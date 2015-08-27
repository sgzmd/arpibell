import socket
import time

#from Foundation import NSUserNotification
#from Foundation import NSUserNotificationCenter
#from Foundation import NSUserNotificationDefaultSoundName

UDP_IP = ''
UDP_PORT = 31716

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))
sock.setblocking(1)

while True:
  data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
  # notification = NSUserNotification.alloc().init()
  # notification.setTitle_("Doorbell!")
  # notification.setInformativeText_(data)
  # notification.setSoundName_(NSUserNotificationDefaultSoundName)

  # center = NSUserNotificationCenter.defaultUserNotificationCenter()
  # center.deliverNotification_(notification)
  time.sleep(5)
  print "received message:", data
