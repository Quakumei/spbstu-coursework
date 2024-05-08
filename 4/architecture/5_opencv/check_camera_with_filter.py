import cv2
import sys
import numpy as np
import dearpygui.dearpygui as dpg


def frame_to_texture(frame):
    data = np.flip(frame, 2)  # because the camera data comes in as BGR and we need RGB
    data = data.ravel()  # flatten camera data to a 1 d stricture
    data = np.asfarray(data, dtype="f")  # change data type to 32bit floats
    texture_data = np.true_divide(
        data, 255.0
    )  # normalize image data to prepare for GPU
    return texture_data


def log_vid_info(vid):
    frame_width = int(vid.get(cv2.CAP_PROP_FRAME_WIDTH))
    frame_height = int(vid.get(cv2.CAP_PROP_FRAME_HEIGHT))
    video_fps = vid.get(cv2.CAP_PROP_FPS)
    print(f"Camera parameters:")
    print(f"Resolution:\t{frame_width}x{frame_height}")
    print(f"FPS:\t\t{video_fps}")

# Init GUI
dpg.create_context()
dpg.create_viewport(
    title="Камера с фильтром",
    width=1300,
    height=700,
    resizable=False,
    vsync=False,
    max_height=700,
    max_width=1300,
)
dpg.setup_dearpygui()
vid = cv2.VideoCapture(0)
if not vid.isOpened():
    print("Cannot open camera")
    sys.exit(1)
log_vid_info(vid)



# Init textures with first frame
ret, frame = vid.read()
texture_data = frame_to_texture(frame)

with dpg.texture_registry(show=True):
    dpg.add_raw_texture(
        frame.shape[1],
        frame.shape[0],
        texture_data,
        tag="texture_tag",
        format=dpg.mvFormat_Float_rgb,
    )
    dpg.add_raw_texture(
        frame.shape[1],
        frame.shape[0],
        texture_data,
        tag="texture_tag_blurred",
        format=dpg.mvFormat_Float_rgb,
    )


with dpg.window(
    label="Blur",
    width=1300,
    height=700,
    no_resize=True,
    no_title_bar=False,
    no_move=True,
    no_scrollbar=True,
    no_collapse=True,
    no_close=True,
):
    # Create blur sliders
    with dpg.group(horizontal=False):
        with dpg.group(horizontal=False):
            dpg.add_text("Blur parameters")
            # Int sliders
            dpg.add_slider_int(
                label="Blur x",
                tag="blur_x",
                default_value=2,
                min_value=1,
                max_value=100,
            )
            dpg.add_slider_int(
                label="Blur y",
                tag="blur_y",
                default_value=2,
                min_value=1,
                max_value=100,
            )
        # Create viewports for camera
        with dpg.group(horizontal=True):
            dpg.add_image("texture_tag")
            dpg.add_image("texture_tag_blurred")

# Start GUI
dpg.show_viewport()

while dpg.is_dearpygui_running():
    ret, frame = vid.read()
    texture_data = frame_to_texture(frame)

    # Apply blur
    blur_x = dpg.get_value("blur_x")
    blur_y = dpg.get_value("blur_y")
    frame = cv2.blur(frame, (blur_x, blur_y))
    texture_data_blurred = frame_to_texture(frame)

    dpg.set_value("texture_tag", texture_data)
    dpg.set_value("texture_tag_blurred", texture_data_blurred)
    dpg.render_dearpygui_frame()

vid.release()
dpg.destroy_context()