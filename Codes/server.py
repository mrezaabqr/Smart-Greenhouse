import flask
from time import time, ctime

app = flask.Flask(__name__)
app.config["DEBUG"] = True


@app.route('/', methods=['GET'])
def get_time():
    t= time()
    return ctime(t)

app.run()