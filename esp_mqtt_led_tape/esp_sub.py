import time
import paho.mqtt.client as mqtt_client
import random
import serial

sen_values = []

def get_connection(port):
    ser = serial.Serial(port,timeout=1)
    return ser

def send(ser,message, mesg_len):
    ser.write(message)
    time.sleep(0.005)
    if mesg_len != 0:
        data = ser.readline()
        result = data.decode()
        result = result.strip()
        return (result)

ser = get_connection("COM9")

def on_message(client, userdata, message):
    global max_value
    global min_value
    data = str(message.payload.decode("utf-8"))
    topic = str(message.topic)
    if topic == 'esp8266-BFBF/range':
        sen_value = float(data)
        print(f"sen_value: {sen_value}")  
        if(sen_value > float(30)):
            send(ser, 'd'.encode(), 0)
        else:
            send(ser, 'u'.encode(), 0)

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
client.subscribe('esp8266-BFBF/range')
time.sleep(600)
client.disconnect()
client.loop_stop()
print('Stop communication')