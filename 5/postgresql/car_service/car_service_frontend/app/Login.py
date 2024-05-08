import streamlit as st

from auth.StreamlitAuth import login_if_not_authorized
from pages.renders.render_about import render_about

from PIL import Image

is_authorized = login_if_not_authorized()
st.title("car_service")
st.markdown("---")
st.image(Image.open("app/pages/resources/car_service_banner.jpg"))
st.markdown("---")
if is_authorized:
    st.info("Используйте элементы сайдбара для навигации по приложению")
st.markdown("---")
render_about()
