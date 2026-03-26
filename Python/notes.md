python is case senstive
python uses indentation instead of brackets
'' vs "" vs ''' '''
and or not
1 is truthy
2 is not

true is converted to 1

None, False, 0, Empty collections: "", (), [], {}


x,y,*z = 1,2,3,4,5

x=1
y=2
z=3,4,5

list are mutable
tuples are immutable

93
94  def sum(a,b,c):
95      return a+b+c
96
97  res=sum(a=10,c=20)
98  print(res)

n Python,
print(f"...") is the syntax for a formatted string literal, also known as an f-string. 
name = "Alice"
age = 25
print(f"My name is {name}, and I am {age} years old.") 
# Output: My name is Alice, and I am 25 years old.


global lexical and nonlocal scope in python

python variables are like vars in js

non local 
used only in function within a function


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