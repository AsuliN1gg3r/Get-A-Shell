import flask
from .models import User
import werkzeug
from . import validation
from . import db
import flask_login

auth = flask.Blueprint('auth', __name__)


@auth.route("/")
def redirect():
    if flask_login.current_user.is_authenticated:
        return flask.redirect(flask.url_for('main.dashboard'))
    return flask.redirect(flask.url_for('auth.login'))


@auth.route("/login", methods=['GET', 'POST'])
def login():
    if flask_login.current_user.is_authenticated:
        return flask.redirect(flask.url_for('main.dashboard'))
    if flask.request.method == 'POST':
        email = flask.request.form['email-input'].lower()
        password = flask.request.form['password-input']

        user = User.query.filter_by(email=email).first()
        if user:
            verify_password = werkzeug.security.check_password_hash(user.password, password)

        if not user or not verify_password:
            flask.flash('Please check your email/password and try again.')
            return flask.redirect(flask.url_for('auth.login'))

        flask_login.login_user(user)
        return flask.redirect(flask.url_for('main.dashboard'))

    return flask.render_template("login.html")

@auth.route("/logout")
@flask_login.login_required
def logout():
    flask_login.logout_user()
    return flask.redirect(flask.url_for("auth.login"))


#! Temporary !#
@auth.route("/signup", methods=['GET', 'POST'])
def signup():
    if flask_login.current_user.is_authenticated:
        return flask.redirect(flask.url_for('main.dashboard'))
    if flask.request.method == 'POST':
        name = flask.request.form['name']
        email = flask.request.form['email'].lower()
        password = flask.request.form['password']

        name_validation = validation.validate_name(name)
        if name_validation == True:
            email_used = User.query.filter_by(email=email).first()
            if not email_used:
                email_validation = validation.validate_email(email)
                if email_validation == True:
                    password_validation = validation.validate_password(password)
                    if password_validation == True:
                        new_user = User(name=name, email=email,
                                        password=werkzeug.security.generate_password_hash(password, method='sha256'))
                        db.session.add(new_user)
                        db.session.commit()

                        flask.flash("User created successfully")
                        return flask.redirect(flask.url_for('auth.login'))
                    else:
                        flask.flash(password_validation)
                else:
                    flask.flash(email_validation)
            else:
                flask.flash(f"Email address {email} is already taken!")
        else:
            flask.flash(name_validation)

        return flask.redirect(flask.url_for('auth.signup'))

    return flask.render_template("signup.html")