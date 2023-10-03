import random, time
import paho.mqtt.client as paho

broker = "broker.emqx.io"
client = paho.Client("client-isu-000000002")	# pass client id

print("Connecting to broker", broker)
client.connect(broker)
client.loop_start()

print("Publishing")
for _ in range(100):
	client.publish("axkuhta/mcu/led", "u")
	time.sleep(1)
	client.publish("axkuhta/mcu/led", "d")
	time.sleep(1)

client.disconnect()
client.loop_stop()









