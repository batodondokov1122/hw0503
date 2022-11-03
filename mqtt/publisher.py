import time
import paho.mqtt.client as mqtt_client
import random
import serial
import numpy as np

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

def normalization(value, min, max):
    return (value - min) / (max - min) * 100

def find_increasing_and_decreasing(arr, threshold):
    for i in range(0,len(arr)-1):
        if arr[i] > threshold:
            decreasing = 0
            increasing += 1
        elif arr[i] < threshold:
            increasing = 0
            decreasing += 1
        if increasing == 4:
            return 1
        elif decreasing == 4:
            return -1

broker="broker.emqx.io"

client = mqtt_client.Client(f'lab_{random.randint(10000, 99999)}')

client.connect(broker)

min = 100
max = 0

if __name__ == '__main__':
    ser = get_connection("COM6")
    moving_arr = []
    while(True):
        sen_value = send(ser, 's'.encode(), 3)
        if sen_value:
            sen_value = int(sen_value)
            norm_sen_value = int(normalization(sen_value, 0, 1023))
            print(f"norm val: {norm_sen_value}")
            if norm_sen_value < min:
                min = norm_sen_value
                client.publish('lab/room100267/photo/min', min)
            elif norm_sen_value > max:
                max = norm_sen_value
                client.publish('lab/room100267/photo/max', max)
            threshold = (max - min) / 2 + min
            client.publish('lab/room100267/photo/instant', norm_sen_value)
            if len(moving_arr)<100: 
                moving_arr.append(norm_sen_value)
            else:
                avg = sum(moving_arr) / len(moving_arr)
                print(f"avg: {avg}")
                client.publish('lab/room100267/photo/averge', norm_sen_value)
                moving_arr.clear()
                moving_arr.append(norm_sen_value)
            result = find_increasing_and_decreasing(moving_arr, threshold)
            if result == 1:
                sen_value = send(ser, 'd'.encode(), 0)
            if result == -1:
                sen_value = send(ser, 'u'.encode(), 0)
                
client.disconnect()
