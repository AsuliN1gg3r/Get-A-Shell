import flask
import flask_sqlalchemy
import flask_login
from flask_socketio import SocketIO, send
import sys
sys.path.insert(1, 'C:\\Users\\Eyal Asulin\\Desktop\\betshemesh-607-get-a-shell\\Web-GUI')
import settings
import subprocess 

db = flask_sqlalchemy.SQLAlchemy()
app = flask.Flask(__name__)
app.config['SECRET_KEY'] = 'key'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///database.db'
db.init_app(app)

login_manager = flask_login.LoginManager()
login_manager.login_view = 'auth.login'
login_manager.init_app(app)

settings.init()
settings.socketio = SocketIO(app)

from .models import Computer

@settings.socketio.on('message')
def handleMessage(msg):
    # Extract computer id, operator and parameters from received message
    computer_id, op_param = msg.split("*")
    operator = op_param[0]
    param = op_param[1:]

    if (operator == 'c'):
        # TODO: execute from real comnputer
        CMD =  subprocess.Popen(param,stdin=subprocess.PIPE,stdout=subprocess.PIPE,stderr=subprocess.PIPE,shell=True)
        result = CMD.stdout.read()
        error = CMD.stderr.read()
        send(result.decode(errors='ignore') if error == b'' else error.decode(errors='ignore'))
    elif (operator == 'n'):
        computer=Computer.query.filter_by(user_id=flask_login.current_user.id, id=int(computer_id)).first()
        computer.name = param
        db.session.commit()
    

from .models import User

@login_manager.user_loader
def load_user(user_id):
    return User.query.get(int(user_id))

from .auth import auth as auth_blueprint
app.register_blueprint(auth_blueprint)

from .main import main as main_blueprint
app.register_blueprint(main_blueprint)

settings.socketio.run(app)

"""def create_app():
    app = flask.Flask(__name__)
    app.config['SECRET_KEY'] = 'key'
    app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
    app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///database.db'
    db.init_app(app)

    login_manager = flask_login.LoginManager()
    login_manager.login_view = 'auth.login'
    login_manager.init_app(app)

    from .models import User

    @login_manager.user_loader
    def load_user(user_id):
        return User.query.get(int(user_id))

    from .auth import auth as auth_blueprint
    app.register_blueprint(auth_blueprint)

    from .main import main as main_blueprint
    app.register_blueprint(main_blueprint)

    return app"""
