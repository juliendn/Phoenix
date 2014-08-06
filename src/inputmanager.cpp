
#include "inputmanager.h"
#include "joystick.h"
#include "keyboard.h"


InputManager::InputManager()
{
}

InputManager::~InputManager()
{
    devices.clear(); // XXX: MEMORY LEAK ??
}

QVariantList InputManager::enumerateDevices()
{
    QVariantList devices;
    devices += Keyboard::enumerateDevices();
    devices += Joystick::enumerateDevices();
    return devices;
}

InputDeviceMapping *InputManager::mappingForDevice(QVariantMap device)
{
    Q_ASSERT(device.contains("class"));
    auto className = device.value("class").toString();
    if (className == "Joystick") {
        return new Joystick::Mapping();
    } else if (className == "Keyboard") {
        return new Keyboard::Mapping();
    } else {
        return nullptr;
    }

//    return InputDeviceMapping();
}

void InputManager::append(InputDevice *device)
{
    devices.push_back(device);
}

InputDevice *InputManager::getDevice(unsigned port) const
{
    return devices.at(port);
}

QList<InputDevice *> InputManager::getDevices() const
{
    return devices;
}

void InputManager::scanDevices()
{
    devices.insert(0, new Joystick());
}
