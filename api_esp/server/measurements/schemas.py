from datetime import datetime
from pydantic import BaseModel


class TemperatureValue(BaseModel):
	"""
	A model of the post data
	"""
	value: float
	location: str
	device_id: str
	timestamp: datetime | None = None
