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

def find_increasing_and_decreasing(arr, threshold): # функция для нахождения убывающих и возрастающих участков рядов измерений
    increasing = 0
    decreasing = 0
    rev_arr = list(reversed(arr))
    for i in range(0,len(rev_arr)-1):
        if rev_arr[i] > threshold:
            decreasing = 0
            increasing += 1
        elif rev_arr[i] < threshold:
            increasing = 0
            decreasing += 1
        if increasing == 4:
            return 1
        elif decreasing == 4:
            return -1
    
max_value = 0
min_value = 0 
ser = get_connection("COM8")

def on_message(client, userdata, message):
    global max_value
    global min_value
    data = str(message.payload.decode("utf-8"))
    topic = str(message.topic)
    if topic == 'lab/room100267/photo/instant':
        sen_value = int(data)
        sen_values.append(sen_value)
        print(f"sen_value: {data}")
        threshold = (max_value - min_value) / 2 + min_value # нахождение порога
        print(f"threshold: {threshold}")
        result = find_increasing_and_decreasing (sen_values,threshold)
        if result == 1: # возрастающий участок измерений - светодиод выключен
            send(ser, 'd'.encode(), 0)
        elif result == -1:# убывающий участок измерений - светодиод включен
            send(ser, 'u'.encode(), 0)
        else: # ничего не происходит - светодиод выключен
            send(ser, 'd'.encode(), 0)
    elif topic == 'lab/room100267/photo/max':
        max_value = int(data)
        print(f"max: {max_value}")
    elif topic == 'lab/room100267/photo/min':
        min_value = int(data)
        print(f"min: {min_value}")
    elif topic == 'lab/room100267/photo/averge':
        avgHundred = float(data)
        print(f"avgHundred: {avgHundred}---------------------------------------")
    elif topic == 'lab/room100267/photo/stream':
        interval = float(data)
        print(f"Interval: {interval} millies")
        
    else:
        print(f"Received meassage on {topic}: {data}")     

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
client.subscribe('lab/room100267/photo/max')
client.subscribe('lab/room100267/photo/min')
client.subscribe('lab/room100267/photo/averge')
client.subscribe('lab/room100267/photo/stream')
time.sleep(600)
client.disconnect()
client.loop_stop()
print('Stop communication')

