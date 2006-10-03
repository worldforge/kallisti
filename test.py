#!/usr/bin/env python
import eris

is_connected = 0
is_logged = 0
is_ig = 0
has_server_info = 0

def connected():
    print "connected called"
    global is_connected
    is_connected = 1

def disconnected():
    print "disconnected called"

def gotServerInfo():
    print "gotServerInfo called"
    global has_server_info
    has_server_info = 1

def disconnecting():
    print "disconnecting called"

def failure():
    print "failure called"

def status_changed():
    print "status_changed called"

def login_success():
    print "login_success called"
    global is_logged
    is_logged = 1

def login_failure():
    print "login_failure called"

got_avatar=None

def avatar_success(avatar):
    print "avatar_success called"
    print avatar
    global is_ig
    global got_avatar
    is_ig = 1
    got_avatar = avatar

def avatar_failure():
    print "avatar_failure called"

def avatar_deactivated():
    print "avatar_deactivated called"

if __name__ == "__main__":

    foo = eris.Connection("foo", "localhost", 6767, 1)

    foo.Connected = connected
    foo.Disconnected = disconnected
    foo.GotServerInfo = gotServerInfo
    foo.Disconnecting = disconnecting
    foo.Failure = failure
    foo.StatusChanged = status_changed

    foo.connect()

    while is_connected == 0:
        eris.polldefault.poll()

    print "Okay"

    foo.refreshServerInfo()

    while has_server_info == 0:
        eris.polldefault.poll()

    print foo.getServerInfo()

    acc = eris.Account(foo)

    acc.LoginSuccess = login_success
    acc.LoginFailure = login_failure

    acc.login("ajr", "hel")

    while is_logged == 0:
        eris.polldefault.poll()

    acc.AvatarSuccess = avatar_success
    acc.AvatarFailure = avatar_failure
    acc.AvatarDeactivated = avatar_deactivated

    for i in acc.getCharacterTypes():
        print "Type: ", i

    acc.createCharacter("foo")

    while not is_ig:
        eris.polldefault.poll()

    view = got_avatar.getView()

    print view
