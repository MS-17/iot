from datetime import datetime
from typing import List
from pydantic import BaseModel


class TemperatureValue(BaseModel):
	"""
	A model of the post request to /data/temperature\n
	value: float\n
	location: str\n
	device_id: str\n
	timestamp: datetime | None = None\n
	"""
	value: float
	location: str
	device_id: str
	timestamp: datetime | None = None


class DataResponseModel(BaseModel):
	"""
	Defines the response model for the /data/temperature/{location}\n
	It will exlude any unnecessary response field, plus it will appear in docs\n
	values: List[float]\n
	location: str\n
	"""
	values: List[float]
	location: str
