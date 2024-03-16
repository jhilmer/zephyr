# Copyright (c) 2022, TOKITA Hiroshi <tokita.hiroshi@gmail.com>
# SPDX-License-Identifier: Apache-2.0

board_runner_args(pyocd "--target=gd32f303zk")
board_runner_args(jlink "--device=GD32F303ZK" "--speed=4000")

include(${ZEPHYR_BASE}/boards/common/pyocd.board.cmake)
include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake)
