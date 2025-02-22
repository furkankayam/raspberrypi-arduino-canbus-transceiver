"""
    Author: Mehmet Furkan KAYA
    Version: Raspberry Pi CANBUS Transmitter
    Arbitration ID: 0x036
"""

import time
import can

bustype = 'socketcan'
channel = 'can0'
bus = can.interface.Bus(channel=channel, bustype=bustype,bitrate=500000)

# Buzzer Active
msg = can.Message(arbitration_id=0x36, data=[1, 1, 3, 1, 4, 1, 1, 2], is_extended_id=False)

# Buzzer Deactivate
# msg = can.Message(arbitration_id=0x36, data=[0, 1, 3, 1, 4, 1, 1, 2], is_extended_id=False)

while True:
	bus.send(msg)
	time.sleep(1)