import random, time
import paho.mqtt.client as paho
import time
import datetime as dt


# esp8266_smn_from_isu/led
topic = input("Input the topic: ")


broker = "broker.emqx.io"
client = paho.Client("client-isu-00002")	# pass client id

print("Connecting to broker", broker)
client.connect(broker)
client.loop_start()

print("Publishing")

# time ranges in which the led is on (for each minute)
ranges = {0: [20, 40], 1: [20, 39], 2: [20, 38], 3: [20, 37], 4: [20, 36], 5: [20, 35], 6: [21, 35], 7: [22, 35], 8: [23, 35], 9: [24, 35], 10:  [25, 35]}

start_time = dt.datetime.now().second
print(f"Start second {start_time}")

c = 0
while(True):
	# wait some time before starting publishing
	time.sleep(ranges[c][0])
	
	# publish in a given time period (send enable led)
	client.publish(topic, "on")	
	time_on = ranges[c][1] - ranges[c][0]
	print(f"Sending on for {time_on} seconds")
	time.sleep(time_on)

	# stop publishing (send disable led)
	client.publish(topic, "off")
	time_off = 60 - ranges[c][1]
	print(f"Sending off for {time_off} seconds")
	time.sleep(time_off)

	# reset the range back to 20 seconds after the 10th minute
	if c == 10:
		c = 0
		continue

	c += 1

	print("Current second: ", dt.datetime.now().second)

client.disconnect()
client.loop_stop()
