from fastapi import APIRouter, Depends
from sqlalchemy.orm import Session
from api_esp.server.measurements.schemas import TemperatureValue
from api_esp.server.database import get_db


router = APIRouter()

@router.get("/temperature")
def get_temperature(location: str):
	return {"message" : "You are in a test route"}

@router.post("/temperature")
def post_temperature(value: TemperatureValue, db: Session = Depends(get_db)):
	return value