import flask
import flask_login
from .models import User, Computer
from flask_socketio import send
import sys
sys.path.insert(1, 'C:\\Users\\Eyal Asulin\\Desktop\\betshemesh-607-get-a-shell\\Web-GUI')
import settings

main = flask.Blueprint('main', __name__)


@main.route('/dashboard')
@flask_login.login_required
def dashboard():
    return flask.render_template('dashboard.html', name=flask_login.current_user.name, count=(len(Computer.query.filter_by(user_id=flask_login.current_user.id).all()), len(Computer.query.filter_by(user_id=flask_login.current_user.id, active=True).all())))

@main.route('/computers')
@flask_login.login_required
def computers():
    return flask.render_template('computers.html', computers=Computer.query.filter_by(user_id=flask_login.current_user.id).all())

@main.route('/computer')
@flask_login.login_required
def computer():
    computer = Computer.query.filter_by(id=int(flask.request.args.get("id"))).first()
    if computer and computer.user_id == flask_login.current_user.id:
        return flask.render_template('computer.html', computer=computer)
    return flask.abort(404)

