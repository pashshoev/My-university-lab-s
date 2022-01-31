import cv2
import numpy as np
import tensorflow as tf
import time
import mediapipe as mp
import matplotlib.pyplot as plt

class_names=["Correct","Incorrect", "No_mask"]


interpreter = tf.lite.Interpreter(model_path='MaskNet.tflite')
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()
interpreter.allocate_tensors()

mpFaceDetection = mp.solutions.face_detection
faceDetection = mpFaceDetection.FaceDetection(0.3)

def decode_pred(pred,class_names):
    mx=-1
    mx_ind=0
    for i in range(pred.shape[0]):
      if pred[i] > mx:
        mx=pred[i]
        mx_ind=i

    className  = class_names[mx_ind] + " " + str(round(mx,3))
    color=(0,0,0)
    if(mx_ind==0):
        color=(0,255,0)
    elif(mx_ind==1):
        color=(0,255,255)
    else:
        color=(0,0,255)
    return className , color


def predict(img):
    img = tf.expand_dims(np.float32(img), 0)
    interpreter.set_tensor(input_details[0]['index'],img)
    interpreter.invoke()
    prediction = interpreter.get_tensor(output_details[0]['index'])
    return prediction
ptime=0
cap=cv2.VideoCapture(0)
while cap.isOpened(): #Пока камера работает
    ret, img= cap.read() # Счиатем очередной кадр из камеры
    img=cv2.flip(img,1) #Отразим кадр горизонтально, так более привычно для нас
    imgRGB=cv2.cvtColor(img, cv2.COLOR_BGR2RGB) # Конвертируем BGR изображение на RGB для обнаружение лиц
    results = faceDetection.process(imgRGB)
    if results.detections:
        for id, detection in enumerate(results.detections):
            bboxC = detection.location_data.relative_bounding_box
            ih, iw, ic = img.shape
            x,y,w,h = int(bboxC.xmin * iw), int(bboxC.ymin * ih), int(bboxC.width * iw), int(bboxC.height * ih)
            if (x < 0):
                x=0
            if y < 0:
                y=0
            face_img = imgRGB[y:y + h + 30, x:x + w]
            face_img = cv2.resize(face_img, (160, 160))
            # # # Далее передаем в функцию которая делает предсказание
            prediction = predict(face_img)
            className, color = decode_pred(prediction[0], class_names)
            cv2.putText(img, className, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX,1, color, 2)
            cv2.rectangle(img, (x, y), (x + w, y + h), color, 5)
    #  считаем FPS и выводим на изображение
    fps=1.0/(time.time() - ptime)
    ptime=time.time()
    cv2.putText(img, "FPS:" + str(int(fps)),(10,30), cv2.FONT_HERSHEY_SIMPLEX, 1.3, (0,255,255), 2)
    #  Выводим обработанное изображение на экран
    cv2.imshow('img', img)
    if(cv2.waitKey(1) & 0xFF== ord('q')):  #  заверщеам цикл при нажатии на "q"
        break
cap.release()
cv2.destroyAllWindows()


