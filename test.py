#!/usr/bin/env python
import eris

is_connected = 0
is_logged = 0

def connected():
    print "connected called"
    global is_connected
    is_connected = 1

def disconnected():
    print "disconnected called"

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

if __name__ == "__main__":

    foo = eris.Connection("foo", "localhost", 6767, 1)

    foo.Connected = connected
    foo.Disconnected = disconnected
    foo.Disconnecting = disconnecting
    foo.Failure = failure
    foo.StatusChanged = status_changed

    foo.connect()

    while is_connected == 0:
        eris.polldefault.poll()

    print "Okay"

    acc = eris.Account(foo)

    acc.LoginSuccess = login_success
    acc.LoginFailure = login_success

    acc.login("ajr", "hel")

    while is_logged == 0:
        eris.polldefault.poll()

