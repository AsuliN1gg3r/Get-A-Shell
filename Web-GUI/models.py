import flask_login
from . import db
import sqlalchemy


class User(flask_login.UserMixin, db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(100), unique=True)
    password = db.Column(db.String(100))
    name = db.Column(db.String(1000))


class Computer(db.Model):
    __tablename__ = 'computer'
    id = db.Column(db.Integer, primary_key=True)
    user_id = db.Column(db.Integer, sqlalchemy.ForeignKey('user.id'))
    ip = db.Column(db.String(15))
    name = db.Column(db.String(30))
    active = db.Column(db.Boolean)
