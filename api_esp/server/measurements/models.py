from sqlalchemy import Column, Integer, Float, String, DateTime

from api_esp.server.database import Base


class TemperatureModel(Base):
	"""
	A table model that the temperature data will be saved in\n
	id = Column(Integer, primary_key=True)\n
	device_id = Column(String)\n
	value = Column(Float)\n
	location = Column(String)\n
	timestamp = Column(DateTime)\n
	"""
	__tablename__ = "temperature"

	id = Column(Integer, primary_key=True)
	device_id = Column(String)
	value = Column(Float)
	location = Column(String)
	timestamp = Column(DateTime)
