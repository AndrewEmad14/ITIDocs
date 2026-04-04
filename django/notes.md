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


  # Django Templates — Blocks, Static Files & Setup

## Project Structure

```
myproject/
├── manage.py
├── static/
│   └── css/
│       └── style.css
├── templates/
│   ├── base.html
│   ├── navbar.html
│   └── home.html
```

---

## 1. Settings Setup

Two things need to be configured in `settings.py` before templates and static files work.

### Templates — tell Django where to look

```python
TEMPLATES = [
    {
        'BACKEND': 'django.template.backends.django.DjangoTemplates',
        'DIRS': [BASE_DIR / 'templates'],  # points to your templates folder
        'APP_DIRS': True,
        ...
    },
]
```

### Static files — tell Django where your CSS/JS lives

```python
STATICFILES_DIRS = [BASE_DIR / 'static']
```

> `BASE_DIR / 'templates'` uses Python's `pathlib` to join paths safely across
> different operating systems — the same idea as `os.path.join()` or Node's `path.join()`.

---

## 2. Template Inheritance

### How it works

You write one `base.html` that holds your navbar, footer, and overall page structure.
Every other page extends it and only fills in what's different.

Django merges them at render time:
1. Load the child template, see `{% extends "base.html" %}`
2. Load `base.html` as the skeleton
3. For each `{% block %}`, use the child's version if defined, otherwise use the base default
4. Output the merged result

### base.html

`{% load static %}` must be the very first line — before even `<!DOCTYPE html>`.

```html
{% load static %}
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="https://fonts.googleapis.com/css2?family=DM+Sans&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="{% static 'css/style.css' %}">
    {% block extra_css %}{% endblock %}
    <title>{% block title %}My Site{% endblock %}</title>
</head>
<body>
    {% block navbar %}
        {% include 'navbar.html' %}
    {% endblock navbar %}

    {% block content %}
    {% endblock content %}

    {% block footer %}
    {% endblock footer %}
</body>
</html>
```

### Child template (e.g. home.html)

`{% extends %}` must always be the very first line of the child template.

```html
{% extends "base.html" %}
{% load static %}

{% block title %}Home{% endblock %}

{% block content %}
<div class="welcome-container">
    <h1>Welcome!</h1>
</div>
{% endblock content %}
```

---

## 3. Blocks

A block is a named slot. The name is just a label you make up — Django doesn't care what it's called, as long as the name in the base matches the name in the child.

```html
{% block content %}{% endblock content %}
```

The name after `endblock` is optional but recommended — it makes large files easier to read.

### Common block names

| Block | Purpose |
|---|---|
| `title` | Sets the browser tab `<title>` |
| `content` | The main page body |
| `navbar` | The navigation bar |
| `footer` | The footer |
| `extra_css` | Page-specific stylesheets |
| `extra_js` | Page-specific scripts |

### Default values

Whatever you put inside a block in `base.html` is the default. If a child doesn't define that block, the default shows. If a child does define it, the child's version completely replaces it.

```html
<!-- base.html — default title -->
<title>{% block title %}My Site{% endblock %}</title>

<!-- about.html — overrides it -->
{% block title %}About — My Site{% endblock %}
```

---

## 4. Static Files

### The `{% static %}` tag

Never hardcode paths like `/static/css/style.css`. Use `{% static %}` instead — it generates the correct URL at runtime and won't break in production.

```html
{% load static %}
<link rel="stylesheet" href="{% static 'css/style.css' %}">
```

`{% load static %}` is required once at the top of any template that uses `{% static %}`.

### Global vs page-specific CSS

Put your global stylesheet in `base.html` so it loads on every page. Use `{% block extra_css %}` for styles that only one page needs.

```html
<!-- base.html -->
<link rel="stylesheet" href="{% static 'css/style.css' %}">  <!-- always loads -->
{% block extra_css %}{% endblock %}                           <!-- optional per-page slot -->
```

```html
<!-- students.html -->
{% extends "base.html" %}
{% load static %}

{% block extra_css %}
    <link rel="stylesheet" href="{% static 'css/students.css' %}">
{% endblock %}
```

---

## 5. Include vs Extends

These are two different concepts that are often used together.

| Tag | What it does |
|---|---|
| `{% extends %}` | Inheritance — child fills in blocks of the parent |
| `{% include %}` | Composition — pastes another file's content at that spot |

`navbar.html` is pulled in with `{% include %}`, so it's just plain HTML with no block tags needed. It doesn't extend anything — it's only ever pasted into `base.html`.

```html
<!-- navbar.html — plain HTML, no blocks needed -->
<nav>
    <a href="{% url 'home' %}">Home</a>
    <a href="{% url 'students' %}">Students</a>
    <a href="{% url 'contact-us' %}">Contact us</a>
</nav>
```

---

## 6. URL Tags

Never hardcode paths in links. Use `{% url %}` with the name defined in `urls.py`.

```python
# urls.py
urlpatterns = [
    path('', views.home, name='home'),
    path('students/', views.students, name='students'),
    path('contact/', views.contact, name='contact-us'),
]
```

```html
<!-- template -->
<a href="{% url 'home' %}">Home</a>
<a href="{% url 'students' %}">Students</a>
```

If you ever change the path in `urls.py`, every `{% url %}` tag updates automatically.

### Passing arguments

```python
# urls.py
path('students/<int:id>/', views.student_detail, name='student-detail'),
```

```html
<a href="{% url 'student-detail' student.id %}">View</a>
```

---

## 7. Connecting a View

The full flow from URL to rendered template:

```python
# views.py
from django.shortcuts import render

def home(request):
    return render(request, 'home.html')

def students(request):
    all_students = Student.objects.all()
    return render(request, 'students.html', {'students': all_students})
```

`render()` finds the template, sees it extends `base.html`, merges the blocks, and returns the final HTML to the browser. Any data you pass in the third argument (a dictionary) becomes available in the template as variables.

---

## Quick Reference

```
{% extends "base.html" %}        — inherit from base (must be line 1)
{% load static %}                — enable {% static %} tag (once per file)
{% block name %}{% endblock %}   — define a named slot
{% include 'file.html' %}        — paste another file's content here
{% static 'css/style.css' %}     — generate URL for a static file
{% url 'view-name' %}            — generate URL for a named route
{% csrf_token %}                 — required inside every POST form
```


# Django Session Notes

## ForeignKey
- FK fields expect the **primary key (integer ID)** in POST requests, not the full object
- Django creates two attributes: `student` (full object) and `student_id` (raw integer)
- In POST, send `"student": 5` — Django maps it to `student_id = 5` in the DB

---

## Querysets

```python
# Filter
Subject.objects.filter(status=1)

# Exclude
Subject.objects.exclude(status=0)

# Order
Subject.objects.all().order_by('-created_at')  # newest first

# Limit
Subject.objects.all()[:10]

# Projection (specific fields)
Subject.objects.values('id', 'name')
Subject.objects.values_list('name', flat=True)

# Distinct
Subject.objects.values('name').distinct()

# Distinct names with first ID
from django.db.models import Min
Subject.objects.values('name').annotate(id=Min('id'))
```

---

## Joins (select_related)

```python
# Fetch related in one query (avoids N+1)
Grade.objects.select_related('student', 'subject').all()

# Access in template with dot notation
grade.student.name
grade.subject.name

# Specific fields with double underscore
Grade.objects.values('grade', 'student__name', 'subject__name')
```

---

## unique_together

Enforce uniqueness on a combination of fields:

```python
class Grade(models.Model):
    student = models.ForeignKey(Student, on_delete=models.CASCADE)
    subject = models.ForeignKey(Subject, on_delete=models.CASCADE)

    class Meta:
        unique_together = ['student', 'subject']
```

Handle violations in the view:

```python
from django.db import IntegrityError
try:
    Grade.objects.create(...)
except IntegrityError:
    # handle duplicate
```

---

## Templates

```django
{# Conditional class #}
<div class="card {% if subject.status == 1 %}active{% endif %}">

{# Compare strings — use single quotes inside HTML attributes #}
<div class="card {% if subject.type == 'math' %}active{% endif %}">

{# Access related fields #}
{{ grade.student.name }}
{{ grade.subject.name }}

{# Loop with empty fallback #}
{% for grade in grades %}
  {{ grade.student.name }}
{% empty %}
  <p>No grades yet.</p>
{% endfor %}

{# Session check #}
{% if user_name %}
    <a href="{% url 'logout' %}">Logout</a>
{% else %}
    <a href="{% url 'login' %}">Login</a>
    <a href="{% url 'register' %}">Register</a>
{% endif %}
```

---

## URL patterns

```python
# Django uses <str:name> not <string:name> (that's Flask)
path("grades_search/<str:name>/", views.grades_search, name="grades_search"),
path("grade_delete/<int:id>/", views.grade_delete, name="grade_delete"),
```

---

## Search (GET params)

```python
# urls.py
path("grades_search/", views.grades_search, name="grades_search"),

# views.py
def grades_search(request):
    name = request.GET.get('student_name', '')  # '' is the default if not found
    grades = Grade.objects.filter(student__name__icontains=name)
    return render(request, "grades.html", {"grades": grades})
```

```html
<form method="GET" action="{% url 'grades_search' %}">
  <input type="text" name="student_name" placeholder="Search by student name">
</form>
```

---

## Sessions

```python
# Set
request.session['user_id'] = user.id
request.session['user_name'] = user.name

# Get
user_id = request.session.get('user_id')       # None if not found
user_id = request.session.get('user_id', 0)    # 0 if not found

# Delete one key
del request.session['user_id']

# Clear all (logout)
request.session.flush()

# Expiry
request.session.set_expiry(0)     # expires on browser close
request.session.set_expiry(3600)  # expires after 1 hour
request.session.set_expiry(None)  # never expires
```

Protect views:
```python
def grades(request):
    if not request.session.get('user_id'):
        return redirect('login')
```

---

## Password Hashing

```python
from django.contrib.auth.hashers import make_password, check_password

# On register — hash before saving
user = User.objects.create(
    name=name,
    email=email,
    password=make_password(password)  # Django auto-generates salt
)

# On login — verify
if check_password(password, user.password):
    # correct password
```

Stored format:
```
pbkdf2_sha256$720000$randomsalt$hashedpassword
```

Django handles the salt automatically — no need to manage it yourself.

---

## Common Mistakes

| Mistake | Fix |
|---|---|
| `class meta` | `class Meta` (capital M) |
| `<string:name>` in URLs | `<str:name>` |
| Using `get` for multiple results | Use `filter` instead |
| Not returning from all branches in a view | Every code path must `return` an HttpResponse |
| Setting session variable but reading different key in template | Keys must match exactly |
| `PGPASSWORD=123` without export | Use `export PGPASSWORD=123` in scripts |



# Django REST Framework — Study Notes

---

## 1. Setup

### Install DRF
```bash
pip install djangorestframework
pip install djangorestframework-authtoken
```

### settings.py
```python
INSTALLED_APPS = [
    'rest_framework',
    'rest_framework.authtoken',
    'your_app',
]

REST_FRAMEWORK = {
    'DEFAULT_AUTHENTICATION_CLASSES': [
        'rest_framework.authentication.TokenAuthentication',
    ],
    'DEFAULT_PERMISSION_CLASSES': [
        'rest_framework.permissions.IsAuthenticated',
    ],
    'DEFAULT_PAGINATION_CLASS': 'rest_framework.pagination.PageNumberPagination',
    'PAGE_SIZE': 10,
}
```

---

## 2. Serializers

### ModelSerializer
Represents relationships using **primary keys (IDs)**.

```python
from rest_framework import serializers
from .models import Student

class StudentSerializer(serializers.ModelSerializer):
    class Meta:
        model = Student
        fields = '__all__'  # or list specific fields: ['id', 'name', 'age']
```

### HyperlinkedModelSerializer
Represents relationships using **full URLs** instead of IDs.

```python
class StudentSerializer(serializers.HyperlinkedModelSerializer):
    class Meta:
        model = Student
        fields = '__all__'
```

| | ModelSerializer | HyperlinkedModelSerializer |
|---|---|---|
| Identifies records by | Primary Key (id) | URL |
| Extra field added | None | `url` field |
| Best for | Most use cases / labs | REST-compliant APIs |

### `fields = '__all__'`
A shortcut that tells DRF to include every field from the model automatically. Not a Django/DRF built-in keyword — DRF checks if `fields` equals the string `'__all__'` and handles it internally.

### write_only fields
```python
class UserSerializer(serializers.ModelSerializer):
    password = serializers.CharField(write_only=True)  # never returned in response
    # or
    class Meta:
        extra_kwargs = {'password': {'write_only': True}}
```

### Overriding create()
DRF's default `create()` calls `Model.objects.create()` which doesn't hash passwords. Override it to use `create_user()`:

```python
def create(self, validated_data):
    return User.objects.create_user(**validated_data)
```

---

## 3. The Three View Approaches

### Functional View (`@api_view`)
```python
from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework import status

@api_view(['GET', 'POST'])
def student_list(request):
    if request.method == 'GET':
        students = Student.objects.all()
        serializer = StudentSerializer(students, many=True)
        return Response(serializer.data)

    elif request.method == 'POST':
        serializer = StudentSerializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
```

### Class-Based View (`APIView`)
```python
from rest_framework.views import APIView

class StudentList(APIView):
    def get(self, request, format=None):
        students = Student.objects.all()
        serializer = StudentSerializer(students, many=True)
        return Response(serializer.data)

    def post(self, request, format=None):
        serializer = StudentSerializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)


class StudentDetail(APIView):
    def get_object(self, pk):
        try:
            return Student.objects.get(pk=pk)
        except Student.DoesNotExist:
            return None

    def get(self, request, pk, format=None):
        student = self.get_object(pk)
        if not student:
            return Response(status=status.HTTP_404_NOT_FOUND)
        serializer = StudentSerializer(student)
        return Response(serializer.data)

    def put(self, request, pk, format=None):
        student = self.get_object(pk)
        if not student:
            return Response(status=status.HTTP_404_NOT_FOUND)
        serializer = StudentSerializer(student, data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

    def patch(self, request, pk, format=None):
        student = self.get_object(pk)
        if not student:
            return Response(status=status.HTTP_404_NOT_FOUND)
        serializer = StudentSerializer(student, data=request.data, partial=True)  # partial=True
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

    def delete(self, request, pk, format=None):
        student = self.get_object(pk)
        if not student:
            return Response(status=status.HTTP_404_NOT_FOUND)
        student.delete()
        return Response(status=status.HTTP_204_NO_CONTENT)
```

### ViewSet
```python
from rest_framework import viewsets

class StudentViewSet(viewsets.ModelViewSet):
    queryset = Student.objects.all()
    serializer_class = StudentSerializer
```

| Feature | APIView | @api_view | ModelViewSet |
|---|---|---|---|
| Pagination | Manual | Manual | Automatic |
| Full control | Yes | Yes | Limited |
| Code amount | Medium | Medium | Minimal |
| Best for | Custom logic | Simple endpoints | Standard CRUD |

---

## 4. URLs & Router

```python
from django.urls import path, include
from rest_framework.routers import DefaultRouter
from . import views

router = DefaultRouter()
router.register(r'students', views.StudentViewSet)

urlpatterns = [
    # Functional views
    path('students/', views.student_list),
    path('students/<int:pk>/', views.student_detail),
    # Class-based views
    path('subjects/', views.SubjectList.as_view()),
    path('subjects/<int:pk>/', views.SubjectDetail.as_view()),
    # ViewSet via router
    path('', include(router.urls)),
]
```

### URL structure rule
```
/students/          → List + Create   (no pk needed)
/students/<pk>/     → Retrieve, Update, Delete (pk required)
```

---

## 5. Pagination

Pagination is **only automatic** in ViewSets/generic views. In `APIView` you must apply it manually.

### Three Pagination Classes

| Class | Navigate by | Best for |
|---|---|---|
| `PageNumberPagination` | `?page=2` | Most cases / labs |
| `LimitOffsetPagination` | `?limit=2&offset=4` | Flexible APIs |
| `CursorPagination` | `?cursor=xxx` | Huge datasets |

### Manual pagination in APIView
```python
from rest_framework.pagination import PageNumberPagination

class SubjectList(APIView):
    def get(self, request, format=None):
        subjects = Subject.objects.all()
        paginator = PageNumberPagination()
        result_page = paginator.paginate_queryset(subjects, request)
        serializer = SubjectSerializer(result_page, many=True)
        return paginator.get_paginated_response(serializer.data)
```

### Paginated response structure
```json
{
    "count": 10,
    "next": "http://localhost:8000/subjects/?page=2",
    "previous": null,
    "results": []
}
```

---

## 6. format_suffix_patterns

Allows appending format extensions to URLs:

```python
from rest_framework.urlpatterns import format_suffix_patterns
urlpatterns = format_suffix_patterns(urlpatterns)
```

| URL | Result |
|---|---|
| `/subjects/` | default format |
| `/subjects.json/` | forced JSON |
| `/subjects.html/` | forced browsable HTML |

This is why views include `format=None` parameter.

---

## 7. PUT vs PATCH

| | PUT | PATCH |
|---|---|---|
| Sends | All fields | Only changed fields |
| `partial=True` | No | Yes |
| Missing fields | Error | Ignored |
| Use case | Full update | Partial update |

```python
# PUT
serializer = StudentSerializer(student, data=request.data)

# PATCH
serializer = StudentSerializer(student, data=request.data, partial=True)
```

---

## 8. ORM Methods

### get() vs filter()

| | `get()` | `filter()` |
|---|---|---|
| Returns | Single object | QuerySet (list) |
| No match | Raises `DoesNotExist` | Returns empty `[]` |
| Multiple matches | Raises `MultipleObjectsReturned` | Returns all matches |

```python
# get() — needs try/except
try:
    student = Student.objects.get(pk=1)
except Student.DoesNotExist:
    return None

# filter() — safe
student = Student.objects.filter(pk=1).first()  # returns None if not found
```

### Common ORM lookups
```python
Student.objects.all()                        # all records
Student.objects.filter(age=25)               # exact match
Student.objects.filter(age__gte=25)          # age >= 25
Student.objects.filter(age__lte=25)          # age <= 25
Student.objects.filter(name__contains="A")   # contains
Student.objects.filter(name__icontains="a")  # case insensitive
Student.objects.filter(email=email).first()  # first match or None
Student.objects.exclude(age=25)              # everything except
```

### ** unpacking (spread)
```python
validated_data = {"name": "Ahmed", "age": 25}

# without unpacking
User(name="Ahmed", age=25)

# with unpacking — same result, cleaner
User(**validated_data)
```

---

## 9. Token Authentication

### Flow
```
POST /login/  →  get token
      ↓
Every request  →  Authorization: Token <your_token>
```

### Login view
```python
from django.contrib.auth import authenticate
from rest_framework.authtoken.models import Token
from rest_framework.decorators import api_view, permission_classes
from rest_framework.permissions import AllowAny

@api_view(['POST'])
@permission_classes([AllowAny])
def login(request):
    username = request.data.get('username')
    password = request.data.get('password')

    user = authenticate(request, username=username, password=password)

    if user:
        token, _ = Token.objects.get_or_create(user=user)
        return Response({'token': token.key}, status=status.HTTP_200_OK)

    return Response({'error': 'Invalid credentials'}, status=status.HTTP_401_UNAUTHORIZED)
```

### Token.objects.get_or_create()
Returns a tuple — always unpack into two variables:
```python
token, created = Token.objects.get_or_create(user=user)
# token   → the Token object
# created → True if new, False if already existed

token, _ = Token.objects.get_or_create(user=user)  # ignore created
```

### Sending token in Bruno / Postman
```
Headers:
  Authorization: Token 9944b09199c62bcf9418ad846dd0e4bbdfc6ee4
```

⚠️ DRF uses `Token` prefix not `Bearer`.

---

## 10. Custom User Model

### Extending AbstractUser
```python
from django.contrib.auth.models import AbstractUser

class User(AbstractUser):
    email = models.EmailField(unique=True)
    created_at = models.DateTimeField(auto_now_add=True)
    website = models.URLField(blank=True, null=True)
    gender = models.CharField(max_length=6, choices=gender_choices)

    USERNAME_FIELD = 'email'   # login with email
    REQUIRED_FIELDS = []       # must not include USERNAME_FIELD

    def __str__(self):
        return self.username
```

### In settings.py
```python
AUTH_USER_MODEL = 'your_app.User'
```

### Why AbstractUser and not models.Model

| Feature | `models.Model` | `AbstractUser` |
|---|---|---|
| `authenticate()` works | No | Yes |
| `Token` works | No | Yes |
| `check_password()` works | No | Yes |
| Password hashing | No | Yes |
| `@permission_classes` works | No | Yes |

### Password hashing methods

```python
# create_user() — hashes automatically (recommended)
User.objects.create_user(**validated_data)

# set_password() — hash + update user.password
user.set_password("plain_password")

# make_password() — returns hash string only
from django.contrib.auth.hashers import make_password
validated_data['password'] = make_password(validated_data['password'])
User.objects.create(**validated_data)
```

---

## 11. Permissions

```python
from rest_framework.permissions import IsAuthenticated, AllowAny

# protect a specific view
class MyView(APIView):
    permission_classes = [IsAuthenticated]

# make a view public
@permission_classes([AllowAny])
def login(request): ...
```

| Class | Behavior |
|---|---|
| `IsAuthenticated` | Only authenticated users |
| `AllowAny` | Everyone, no auth needed |
| `IsAdminUser` | Only staff/admin users |
| `IsAuthenticatedOrReadOnly` | Auth users get full access, others read-only |

---

## 12. Key HTTP Status Codes in DRF

```python
status.HTTP_200_OK             # success GET
status.HTTP_201_CREATED        # success POST
status.HTTP_204_NO_CONTENT     # success DELETE
status.HTTP_400_BAD_REQUEST    # invalid data
status.HTTP_401_UNAUTHORIZED   # not authenticated
status.HTTP_404_NOT_FOUND      # resource not found
```