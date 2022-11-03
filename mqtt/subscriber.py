import time
import paho.mqtt.client as mqtt_client
import random

values = []

def on_message(client, userdata, message):
    data = str(message.payload.decode("utf-8"))
    # print(f"Received meassage on topic: {data}")

broker="broker.emqx.io"

client = mqtt_client.Client(f'lab_{random.randint(10000, 99999)}')
client.on_message = on_message

try:
    client.connect(broker)
except Exception:
    print('Failed to connect. Check network')
    exit()
    
client.loop_start()

wait_time = 5
sleep_time = 1   
while not client.is_connected():
    time.sleep(sleep_time)
    wait_time -= sleep_time
    if not wait_time:
        raise ValueError('Failed to connect. Timeout')
    
print('Subscribing')
client.subscribe('lab/room100267/photo/instant')
time.sleep(600)
print
client.disconnect()
client.loop_stop()
print('Stop communication')