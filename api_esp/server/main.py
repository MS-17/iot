from fastapi import FastAPI
from api_esp.server.measurements import router
from api_esp.server.database import init_db


app = FastAPI()
app.include_router(
	router=router.router,
	prefix="/data",
	tags=["data"],
	responses={404: {"description": "Not found"}}
	)

init_db()

@app.get("/")
def root():
	return {"message" : "The application starts here"}
