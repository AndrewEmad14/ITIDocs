python3 -m venv venv
 source venv/bin/activate
(venv)  pip freeze > requirements.txt
(venv)  ✗ pip install -r requirements.txt

django-admin startproject itiSite .
python manage.py runserver
python manage.py startapp your_app_name
python magange.py makemigrations
python manage.py migrate

Projects vs. apps

What’s the difference between a project and an app? An app is a web application that does something – e.g., a blog system, a database of public records or a small poll app. A project is a collection of configuration and apps for a particular website. A project can contain multiple apps. An app can be in multiple projects.



steps of createing an app

python manage.py startapp your_app_name

if you have request and routes comming up you should create a urls.py folder
should be someting like this:

from django.urls import path

from . import views

urlpatterns = [
    path("", views.index, name="index"),
]

python manage.py migrate
The migrate command looks at the INSTALLED_APPS setting and creates any necessary database tables according to the database settings in your mysite/settings.py file and the database migrations shipped with the app


add your config in the project/setting.py installed apps

python manage.py makemigrations polls
python manage.py migrate



setting up the admin
$ python manage.py createsuperuser


to show up in the admin board

in the app/admin.py
import your model

admin.site.register(your_model)





pip install psycopg2-binary python-dotenv


postgres setup 
  install postgres version and run the service
  install a gui 
  connect to local host and the username should be either your own user name(you can know with whoami) or create your own super user







nav bar 
  home
  students
  subjects
  grade
  userprofile
  logout

students
  student display
  student crud

subjects
  search display 
  search crud

grades
  search studentid or subjectname 
  grad display
  grade crud


user must be logged in to got to home

BOUNS
  leaderboard best 5 students 
  student name , subjects ,total
  

  django token 
  django rest framework
  viewset automation
  signals