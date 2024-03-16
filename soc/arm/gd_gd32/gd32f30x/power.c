/*
 * Copyright (c) 2023 Google LLC
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <soc.h>

#include <gd32f30x.h>

#include <zephyr/drivers/clock_control/stm32_clock_control.h>
#include <zephyr/drivers/counter.h>
#include <zephyr/drivers/interrupt_controller/gic.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/pm/pm.h>
#include <zephyr/init.h>

LOG_MODULE_DECLARE(soc, CONFIG_SOC_LOG_LEVEL);

void pm_state_set(enum pm_state state, uint8_t substate_id)
{
	LOG_DBG("pm_state_set %u", state);
	switch (state) {
	case PM_STATE_SUSPEND_TO_IDLE:
#if 0
		set_mode_stop(substate_id);
		/* Set SLEEPDEEP bit of Cortex System Control Register */
		LL_LPM_EnableDeepSleep();
		/* Select mode entry : WFE or WFI and enter the CPU selected mode */
#endif
        pmu_to_sleepmode(WFI_CMD);
		k_cpu_idle();
		break;
	case PM_STATE_STANDBY:
#if 0
		LL_PWR_SetPowerMode(LL_PWR_MODE_STANDBY);
		LL_LPM_EnableDeepSleep();
		LL_DBGMCU_DisableDBGStandbyMode();
#endif
		k_cpu_idle();
		break;
	default:
		LOG_DBG("Unsupported power state %u", state);
		return;
	}

}

/* Handle SOC specific activity after Low Power Mode Exit */
void pm_state_exit_post_ops(enum pm_state state, uint8_t substate_id)
{
	LOG_DBG("pm_state_exit_post_ops %u", state);
	switch (state) {
	case PM_STATE_SUSPEND_TO_IDLE:
#if 0
		if (substate_id <= 3) {
			LL_LPM_DisableSleepOnExit();
			LL_LPM_EnableSleep();
		} else {
			LOG_DBG("Unsupported power substate-id %u",
							substate_id);
		}
		/* need to restore the clock */
		stm32_clock_control_init(NULL);

		/*
		 * System is now in active mode.
		 * Reenable interrupts which were disabled
		 * when OS started idling code.
		 */
#endif
		irq_unlock(0);
		break;
	case PM_STATE_STANDBY:
		__fallthrough;
	case PM_STATE_SUSPEND_TO_RAM:
		__fallthrough;
	case PM_STATE_SUSPEND_TO_DISK:
		__fallthrough;
	default:
		LOG_DBG("Unsupported power state %u", state);
		break;
	}

}
