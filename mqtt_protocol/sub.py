import random, time
import paho.mqtt.client as paho
from serial import Serial

responses = {'u': 7, 'd': 6}
port = "/dev/ttyUSB0"

# if it doesn't work check the baudrate here and on the microcontroller (Serial begin (9600))
connection = Serial(port, timeout=1)


def send_command(cmd, response_len):
	connection.write(cmd.encode())	# cmd is a command


def on_message(client, user_data, message):
	time.sleep(1)
	data = str(message.payload.decode("utf-8"))
	send_command(data, responses[data])


broker = "broker.emqx.io"
client = paho.Client("client-isu-000000001")	# pass client id, it should be unique for pub and sub

client.on_message = on_message

print("Connecting to broker", broker)
client.connect(broker)
client.loop_start()

print("Subscribing")
client.subscribe("sergei/mcu/led")
time.sleep(30)

client.disconnect()
client.loop_stop()




