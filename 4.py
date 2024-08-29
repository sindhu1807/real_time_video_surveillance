import cv2
import datetime
import numpy as np
import os

# Configuration
rtsp_link = 'rtsp://your_rtsp_link_here'  # Replace with your RTSP link
output_folder = 'motion_logs'
frame_interval = 60  # Save frame every 60 seconds

# Ensure the output folder exists
os.makedirs(output_folder, exist_ok=True)

# Initialize video capture
cap = cv2.VideoCapture(rtsp_link)

# Check if the capture is successful
if not cap.isOpened():
    print("Error: Could not open video stream.")
    exit()

# Function to add timestamp to frame
def add_timestamp(frame):
    timestamp = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    cv2.putText(frame, timestamp, (10, frame.shape[0] - 10), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 0), 2, cv2.LINE_AA)
    return frame

# Function to detect motion
def detect_motion(prev_frame, curr_frame):
    # Convert frames to grayscale
    prev_gray = cv2.cvtColor(prev_frame, cv2.COLOR_BGR2GRAY)
    curr_gray = cv2.cvtColor(curr_frame, cv2.COLOR_BGR2GRAY)
    
    # Compute absolute difference between frames
    diff = cv2.absdiff(prev_gray, curr_gray)
    
    # Threshold the difference to get the binary image
    _, thresh = cv2.threshold(diff, 50, 255, cv2.THRESH_BINARY)
    
    # Find contours in the thresholded image
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    # If any contour is detected, return True
    if len(contours) > 0:
        return True
    return False

# Initialize variables
prev_frame = None
last_save_time = datetime.datetime.now()

while True:
    ret, frame = cap.read()
    if not ret:
        print("Error: Could not read frame.")
        break
    
    # Add timestamp to the frame
    frame = add_timestamp(frame)
    
    # Detect motion if previous frame is available
    if prev_frame is not None:
        if detect_motion(prev_frame, frame):
            timestamp = datetime.datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
            filename = os.path.join(output_folder, f'motion_{timestamp}.jpg')
            cv2.imwrite(filename, frame)
            print(f"Motion detected. Frame saved as {filename}.")
    
    # Save a frame every 'frame_interval' seconds
    current_time = datetime.datetime.now()
    if (current_time - last_save_time).total_seconds() >= frame_interval:
        filename = os.path.join(output_folder, f'routine_{current_time.strftime("%Y-%m-%d_%H-%M-%S")}.jpg')
        cv2.imwrite(filename, frame)
        last_save_time = current_time
        print(f"Routine frame saved as {filename}.")
    
    # Display the frame
    cv2.imshow('Video Stream', frame)
    
    # Exit on pressing 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    
    # Update previous frame
    prev_frame = frame

# Release resources
cap.release()
cv2.destroyAllWindows()
