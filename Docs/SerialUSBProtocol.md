--WORK IN PROGRESS--

# Serial USB Protocol

Describes the structure and packets of the controller interface.

## To Controller Commands:

| ID | Name | Argument Bytes | Description |
| -- | ---- | -------------- | ----------- |
| 0x06 | TX_INDICATORS | 2 | Send all 16 indicator states to the controller as a UINT16 integer. |
| 0x08 | TX_BACKLIGHT | 2 | Send the backlight brightnes as a UINT16 integer. |
| 0x09 | TX_IND_BRIGHT | 2 | Send the indicator brighness as a UINT16 integer. |
| 0x0A | TX_MAX_IND_BRIGHT | 1 | Send the maximum brightness of the indicators. This sets the digital pot connected to the STP16CP05. [See the Schematic for more.](./GarminAutopilotREV3.pdf) |
| 0x11 | TX_START_STREAM | 0 | Sets the controller into [stream-mode.](#stream-mode) |
| 0x12 | TX_STOP_STREAM | 0 | Removes the controller from [stream-mode.](#stream-mode) |
| 0xF1 | TX_OPTIONS | 2? | -- WIP -- Send config Options to the controller. |
| 0xFF | RX_TX_ERROR | 1 | Sent when the companion app has an error. Performs a non-hardware reset of the controller |
| 0xFE | RX_HELLO | 0 | Sent when the companion app wants to check the connection status of the controller. The controller echos back the command when received. |

## From Controller Commands:

| ID | Name | Argument Bytes | Description |
| -- | ---- | -------------- | ----------- |
| 0x02 | RX_BUTTONS | 3 | Gets the state of all [Buttons](#Button-State-Mask) from the controller. |
| 0x03 | RX_ENC_DIR | 2 | Gets the [Encoder Directions](#Encoder-Directions) from the controller. |
| 0x04 | RX_ENC_POS | 5 | Gets the internal position of the encoders from the controller. |
| 0x05 | RX_STREAM | 5 | When in [Stream Mode](#stream-mode) the controller sends the button states and encoder directions in one packet. |
| 0xF2 | RX_STATUS | 2? | -- WIP -- Gets a detailed status report from the controller. |

# Stream Mode

When the controller is set to stream-mode, every time a button or encoder state changes, it sends a RX_STREAM command over the serial bus. This needs to be activated and deactivated by the host. An event is fired for both button press and release changes. With the data in the packet reflecting the change.

### Stream Command Structure:

| Bit Indecies | Name | Size in bits | Description |
| -- | ---- | -------------- | ----------- |
| 0 - 17 | Buttons | 18 | Individual button states (1 = Pressed, 0 = Released) |
| 24 - 33 | Encoders | 10 | [Encoder Directions](#encoder-directions) |

### Button States Mask:

| Index | Name |
| ----- | ---- |
| 0 | HDG |
| 1 | APR |
| 2 | BC |
| 3 | NAV |
| 4 | FD |
| 5 | BANK |
| 6 | AP |
| 7 | XFR |
| 8 | YD |
| 9 | ALT |
| 10 | VS |
| 11 | VNV |
| 12 | FLC |
| 13 | SPD |
| 14 | CRS1-ENC |
| 15 | CRS2-ENC |
| 16 | HDG-ENC |
| 17 | ALT-ENC |

## Encoder Directions

| Binary | Hex | Direction | Clock |
| ------ | --- | --------- | ----- |
| 0b00   | 0x0 | Decrement | Counter-Clockwise |
| 0b01   | 0x1 | Still | N/A |
| 0b11   | 0x2 | Increment | Clockwise |