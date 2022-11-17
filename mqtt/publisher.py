import time
import paho.mqtt.client as mqtt_client
import random
import serial

def get_connection(port):
    ser = serial.Serial(port,timeout=0)
    return ser

def send(ser,message, mesg_len):
    ser.write(message)
    time.sleep(0.005)
    if mesg_len != 0:
        data = ser.readline()
        result = data.decode()
        result = result.strip()
        return (result)
    
def read(ser):   
    data = ser.readline()
    result = data.decode()
    result = result.strip()
    return (result)

def normalization(value, min, max): # функция для нормирования показаний сенсора в диапазоне от 0 до 100
    return (value - min) / (max - min) * 100

broker="broker.emqx.io"
client = mqtt_client.Client(f'lab_{random.randint(10000, 99999)}')
client.connect(broker)

min = 100
max = 0
stream = 1000.0
interval_is_chosen = False
streaming = False
if __name__ == '__main__':
    ser = get_connection("COM7")
    moving_arr = [] # список для очереди из ста значений 
    while(True):
        if not streaming: # включение потоковой передачи данных
            send(ser, 's'.encode(), 0)
        sen_value = read(ser)
        if sen_value:
            streaming = True
            if ser.in_waiting >= 0: # автоматическое определение времени между измерениями
                if (ser.inWaiting() >= 3 and interval_is_chosen != True):
                    send(ser,'h'.encode(),0) # увеличивает кол-во миллисекунд меду измерениями на микроконтроллере
                    stream += 10
                    interval_is_chosen = True # у меня программа начинает несправляться если время меньше 720 миллисекунд
                    client.publish('lab/room100267/photo/stream', stream)
                elif (ser.inWaiting() == 0): 
                    send(ser,'l'.encode(),0)# уменьшает кол-во миллисекунд меджу измерениями на микроконтроллере
                    stream -= 10
            sen_value = int(sen_value)
            norm_sen_value = int(normalization(sen_value, 0, 1023)) 
            print(f"norm val: {norm_sen_value}")
            if norm_sen_value < min:
                min = norm_sen_value # поиск и обновление минимального значения
            elif norm_sen_value > max:
                max = norm_sen_value # поиск и обновление максимального значения
            client.publish('lab/room100267/photo/min', min)
            client.publish('lab/room100267/photo/max', max)
            client.publish('lab/room100267/photo/instant', norm_sen_value)
            if len(moving_arr) < 100: # передача усредненных данных по 100 значениям (бегущим средним).
                moving_arr.append(norm_sen_value)
            else:
                avg = sum(moving_arr) / len(moving_arr)
                client.publish('lab/room100267/photo/averge', avg)
                moving_arr.clear()
                moving_arr.append(norm_sen_value)
            time.sleep(stream / 1000)
client.disconnect()