from System import Byte


class I2CRegisterDevice:
    def __init__(self, slave, identity_register, identity_value, sample_registers):
        self.slave = slave
        self.pointer = 0
        self.registers = [0] * 256
        self.fixed_registers = set()

        self.registers[identity_register] = identity_value
        self.fixed_registers.add(identity_register)
        for register, value in sample_registers.items():
            self.registers[register] = value
            self.fixed_registers.add(register)

        self.slave.DataReceived += self.on_data_received
        self.slave.ReadRequested += self.on_read_requested
        self.slave.TransmissionFinished += self.on_transmission_finished

    def on_data_received(self, data):
        if len(data) == 0:
            return

        self.pointer = int(data[0]) & 0xFF
        for value in data[1:]:
            self.write_register(self.pointer, int(value) & 0xFF)
            self.pointer = (self.pointer + 1) & 0xFF

    def on_read_requested(self, count):
        self.slave.Reset()
        for unused in range(int(count)):
            self.slave.EnqueueResponseByte(Byte(self.registers[self.pointer]))
            self.pointer = (self.pointer + 1) & 0xFF

    def on_transmission_finished(self):
        # Clear any unread response bytes, but retain the device register pointer.
        self.slave.Reset()

    def write_register(self, register, value):
        if register not in self.fixed_registers:
            self.registers[register] = value


_mpu_samples = {
    0x3B: 0x01, 0x3C: 0x20,
    0x3D: 0xFF, 0x3E: 0xE0,
    0x3F: 0x40, 0x40: 0x00,
}
_ak8963_samples = {
    0x03: 0x34, 0x04: 0x12,
    0x05: 0x78, 0x06: 0x56,
    0x07: 0xBC, 0x08: 0x9A,
}

# Keep model instances alive for the lifetime of the emulation. Register values
# persist when the MCU is reset and the ELF is reloaded.
_lgt92_i2c_models = [
    I2CRegisterDevice(monitor.Machine["sysbus.i2c1.mpu9250"], 0x75, 0x71, _mpu_samples),
    I2CRegisterDevice(monitor.Machine["sysbus.i2c1.ak8963"], 0x00, 0x48, _ak8963_samples),
]
