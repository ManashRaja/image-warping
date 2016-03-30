from cv2 import *
import cv2
import numpy as np

def rotateImage(img,alpha,beta,gamma,dx,dy,dz,f):
    alpha = (alpha - 90.0) * np.pi / 180.0
    beta = (beta - 90.0) * np.pi / 180.0
    gamma = (gamma - 90.0) * np.pi / 180.0

    w, h = img.shape[:2]
    A1 = np.float32([
                    [1, 0, -w / 2],
                    [0, 1, -h / 2],
                    [0, 0, 0],
                    [0, 0, 1]])
    RX = np.float32([
                    [1, 0, 0, 0],
                    [0, np.cos(alpha), -np.sin(alpha), 0],
                    [0, np.sin(alpha), np.cos(alpha), 0],
                    [0, 0, 0, 1]])

    RY = np.float32([
                    [np.cos(beta), 0, -np.sin(beta), 0],
                    [0, 1, 0, 0],
                    [np.sin(beta), 0, np.cos(beta), 0],
                    [0, 0, 0, 1]])

    RZ = np.float32([
                    [np.cos(gamma), -np.sin(gamma), 0, 0],
                    [np.sin(gamma), np.cos(gamma), 0, 0],
                    [0, 0, 1, 0],
                    [0, 0, 0, 1]])
    R = np.mat(RX) * np.mat(RY) * np.mat(RZ)
    T = np.float32([[1, 0, 0, dx], [0, 1, 0, dy], [0, 0, 1, dz], [0, 0, 0, 1]])
    A2 = np.float32([[f, 0, w / 2, 0], [0, f, h / 2, 0], [0, 0, 1, 0]])
    trans = np.mat(A2) * (np.mat(T) * (np.mat(R) * np.mat(A1)))
    out = cv2.warpPerspective(img, trans, (h, w), flags=cv2.INTER_LANCZOS4)
    return out



vc = cv2.VideoCapture(0)
if vc.isOpened():
    rval, frame = vc.read()
else:
    rval = False

if rval:
    rval, frame = vc.read()
    dst = rotateImage(frame, 105, 90, 90, 0, 0, 200, 200)
    cv2.imshow("Image", dst)
    cv2.waitKey(0)
vc.release()