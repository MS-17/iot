from fastapi import APIRouter, Depends
from sqlalchemy.orm import Session

from api_esp.server.measurements.schemas import TemperatureValue, DataResponseModel
from api_esp.server.measurements.models import TemperatureModel
from api_esp.server.database import get_db


router = APIRouter()

@router.get("/")
def get_all(db:Session = Depends(get_db)):
	return db.query(TemperatureModel).all()

@router.get("/temperature/{location}", response_model=DataResponseModel)
def get_temperature(location: str, db: Session = Depends(get_db)):
	result = db.query(TemperatureModel).filter(TemperatureModel.location == location).all()
	data = {
		"values": [record.value for record in result],
		"location": location
	}
	return data

@router.post("/temperature")
def post_temperature(data: TemperatureValue, db: Session = Depends(get_db)):
	db_data = TemperatureModel(device_id = data.device_id, value = data.value, 
								location = data.location.lower(),
								timestamp = data.timestamp)
	db.add(db_data)
	db.commit()
	db.refresh(db_data)
	return db_data
