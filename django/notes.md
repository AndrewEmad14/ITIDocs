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
    path("", views.index, name="index"),ze
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



steps for using drf
1. create a model
2. create a serilizer
3. create a view set/class/function
4. create a url
5. put the url in the urls.py project file
6. put your new app inside the installed apps in settings.py




# Session Summary — 2026-04-16 — Django DRF Projects App

## What We Covered

We worked through the architecture and implementation of a Django + DRF crowdfunding backend. The session covered app structure decisions, model design, serializer patterns, URL routing, and Docker workflow. Every decision was driven by real constraints — a 4-day deadline and a team working in parallel.

---

## Key Concepts Learned

### 1. Django App Structure & Merge Conflict Strategy
- **What it is:** Django projects are split into apps. Each app owns its own `models.py`, `views.py`, `serializers.py`, `urls.py`.
- **Why it matters:** Separate apps = separate files = isolated git diffs. Keeping `Tags` and `Categories` in separate apps means teammates never touch the same file simultaneously.
- **Decision made:** Since DB was not empty and deadline was 4 days, we chose **not to refactor** the existing code. Ship it, extract after submission.
- **Rule established:** Nobody touches `projects/models.py` without notifying the team first.
- **Doc:** [Django Reusable Apps](https://docs.djangoproject.com/en/stable/intro/reusable-apps/)

---

### 2. Nested Apps & AppConfig
- **What it is:** When apps live under an `apps/` directory, Django needs the full dotted path in `AppConfig.name`.
- **Why it matters:** If left as just `"tags"`, Django won't locate the app correctly.
- **Example:**
```python
# apps/tags/apps.py
class TagsConfig(AppConfig):
    name = "apps.tags"  # NOT just "tags"
```
- **INSTALLED_APPS entry:**
```python
"apps.tags.apps.TagsConfig"
```
- **Doc:** [AppConfig.name](https://docs.djangoproject.com/en/stable/ref/applications/#django.apps.AppConfig.name)

---

### 3. ForeignKey `on_delete` — PROTECT vs RESTRICT
- **What it is:** Controls what happens to related objects when the referenced object is deleted.
- **Why it matters:** Wrong `on_delete` = silent data corruption or unexpected deletions.
- **Decision made:**
  - `category` → `PROTECT` — blocks deletion of a category if any project references it
  - `user` → `PROTECT` — users are never deleted, only deactivated via `is_activated=False`
- **PROTECT vs RESTRICT:**
  - `PROTECT` — blocks delete. Full stop. No exceptions.
  - `RESTRICT` — blocks delete **unless** the referencing object is also being deleted in the same operation via a CASCADE chain.
- **Example:**
```python
category = models.ForeignKey(
    'categories.Category',
    on_delete=models.PROTECT,
    null=True
)
user = models.ForeignKey(
    'profiles.User',
    on_delete=models.PROTECT
)
```
- **Doc:** [Django on_delete](https://docs.djangoproject.com/en/stable/ref/models/fields/#django.db.models.ForeignKey.on_delete)

---

### 4. FK Naming Convention — Avoid `_id` Suffix
- **What it is:** Django automatically appends `_id` to FK fields at the DB column level.
- **Why it matters:** Naming your FK `category_id` in Python causes Django to create a `category_id_id` column in the DB.
- **Correct pattern:**
```python
# Wrong
category_id = models.ForeignKey(Category, ...)  # creates category_id_id in DB

# Correct
category = models.ForeignKey(Category, ...)  # creates category_id in DB
```
- **Doc:** [Django ForeignKey DB representation](https://docs.djangoproject.com/en/stable/ref/models/fields/#database-representation)

---

### 5. Soft Delete Pattern
- **What it is:** Instead of deleting a user record, you deactivate it by setting a boolean flag.
- **Why it matters:** Preserves all relational data — donations, projects, ratings remain traceable. Hard deletes cascade problems across your schema.
- **Implementation:** Use the existing `is_activated` field on `Users`:
```python
# Never do this
user.delete()

# Always do this
user.is_activated = False
user.save()
```

---

### 6. TextChoices for Enum Fields
- **What it is:** A Django built-in way to define enumerated field values with dot-access.
- **Why it matters over raw tuples:** Type safety, IDE autocomplete, no raw string typos in filters.
- **Tuple way (old):**
```python
STATUS = {("pending", "Pending"), ("banned", "Banned")}
# Risk: Project.objects.filter(status="pendingg") — silent bug
```
- **TextChoices way (correct):**
```python
class Status(models.TextChoices):
    BANNED = "banned", "Banned"
    PENDING = "pending", "Pending"
    FINISHED = "finished", "Finished"
    CANCELED = "canceled", "Canceled"

status = models.CharField(
    max_length=20,
    choices=Status.choices,
    default=Status.PENDING
)

# Safe filtering
Project.objects.filter(status=Project.Status.PENDING)
```
- **Doc:** [Django TextChoices](https://docs.djangoproject.com/en/stable/ref/models/fields/#enumeration-types)

---

### 7. ManyToManyField — No Junction Model Needed
- **What it is:** Django handles junction tables automatically for M2M relationships.
- **Why it matters:** You don't need to write a `Project_Tag` model — Django creates and manages that table for you.
- **Example:**
```python
# No need for Project_Tag model
tags = models.ManyToManyField('tags.Tag')
```
- **Doc:** [Django ManyToManyField](https://docs.djangoproject.com/en/stable/ref/models/fields/#manytomanyfield)

---

### 8. Computed Fields — avg_rate Should Not Be Stored
- **What it is:** Fields derived from other tables should be computed at query time, not stored.
- **Why it matters:** A stored `avg_rate` goes stale the moment a new `Rating` is inserted.
- **Correct approach:** Use `annotate()` with `Avg` at the DB level — one SQL `AVG()` call, no extra memory overhead.
- **Example:**
```python
from django.db.models import Avg

Project.objects.annotate(avg_rate=Avg('ratings__rate'))
```
- **Doc:** [Django Aggregation](https://docs.djangoproject.com/en/stable/topics/db/aggregation/#avg)

---

### 9. SerializerMethodField
- **What it is:** A DRF serializer field whose value comes from a method you define — not a model attribute.
- **Why it matters:** Used for computed values, concatenated fields, or anything not directly on the model.
- **Naming convention:** Method must be named `get_<field_name>` and receives `obj` (the model instance).
- **Example:**
```python
class ProjectSerializer(serializers.ModelSerializer):
    category = serializers.ReadOnlyField(source='category.name')
    user_fullname = serializers.SerializerMethodField()
    avg_rate = serializers.SerializerMethodField()

    class Meta:
        model = Project
        fields = '__all__'

    def get_user_fullname(self, obj):
        return f"{obj.user.first_name} {obj.user.last_name}"

    def get_avg_rate(self, obj):
        from django.db.models import Avg
        result = obj.rating_set.aggregate(Avg("rate", default=0))
        return result["rate__avg"]
```
- **Doc:** [DRF SerializerMethodField](https://www.django-rest-framework.org/api-guide/fields/#serializermethodfield)

---

### 10. DRF Router URL Doubling Bug
- **What it is:** When your main `urls.py` prefixes with `api/projects/` and your router also registers `r"projects"`, the endpoint becomes `api/projects/projects/`.
- **Why it matters:** Results in a 404 that's hard to spot without inspecting registered URLs.
- **How we caught it:**
```bash
python manage.py show_urls | grep projects
```
- **Fix — register router with empty prefix:**
```python
router.register(r"", ProjectViewSet)  # not r"projects"
```
- **Doc:** [DRF Routers](https://www.django-rest-framework.org/api-guide/routers/)

---

### 11. Debugging URLs with django-extensions
- **What it is:** A third-party package that adds `show_urls` management command among other utilities.
- **Why it matters:** Lets you inspect every registered URL, its view, and its name — essential for debugging 404s.
- **Installation:**
```bash
pip install django-extensions
# Add to INSTALLED_APPS
"django_extensions"
```
- **Usage:**
```bash
python manage.py show_urls
python manage.py show_urls | grep projects  # filter by app
```
- **Doc:** [django-extensions](https://django-extensions.readthedocs.io/en/latest/)

---

### 12. Docker — Installing New Packages
- **What it is:** Since your local directory is volume-mounted into the container, package changes require a rebuild.
- **Why it matters:** Code changes reflect instantly via the volume, but new packages need to be baked into the image layer.
- **Workflow:**
```bash
# Option A — locally with venv
pip install django-extensions
pip freeze > requirements.txt
docker compose up --build

# Option B — directly in running container
docker compose exec backend pip install django-extensions
docker compose exec backend pip freeze > requirements.txt
docker compose up --build
```
- **Doc:** [Docker Compose exec](https://docs.docker.com/engine/reference/commandline/compose_exec/)

---

### 13. Docker — Cleaning Dangling Images
- **What it is:** Every `--build` can leave behind untagged image layers that consume disk space.
- **Commands:**
```bash
# Safe — removes only dangling (untagged, unreferenced) images
docker image prune

# Aggressive — removes all unused images (containers must be running to protect them)
docker image prune -a
```
- **Doc:** [Docker image prune](https://docs.docker.com/engine/reference/commandline/image_prune/)

---

### 14. pip freeze Limitations
- **What it is:** `pip freeze` dumps every installed package including transitive dependencies you never explicitly chose.
- **Why it matters:** Pollutes `requirements.txt` with packages you don't own, at pinned versions you didn't vet.
- **Better approach (post-deadline):** Use `pip-tools` — maintain a clean `requirements.in` and let it generate the full `requirements.txt`.
```
# requirements.in
django
djangorestframework
django-extensions
```
```bash
pip-compile requirements.in  # generates requirements.txt
```
- **Doc:** [pip-tools](https://pip-tools.readthedocs.io/en/latest/)

---

## Problems We Worked Through

| Problem | Root Cause | Resolution |
|---|---|---|
| 404 on `/api/projects/` | Router registered `r"projects"` on top of `api/projects/` prefix | Changed to `router.register(r"", ProjectViewSet)` |
| `category_id_id` DB column risk | FK named `category_id` in Python | Renamed to `category` — Django appends `_id` automatically |
| `avg_rate` staleness | Stored as a field on `Project` | Moved to `SerializerMethodField` using `Avg` aggregation |
| Can't install packages in Docker | Volume mount shadows container `/app` | Install locally or via `exec`, then `--build` |
| `SerilazerMethodField` typo | Misspelling | `SerializerMethodField` |
| Missing `return` in serializer method | Python silent None return | Added explicit `return` statement |
| `Rating.filter()` invalid | Missing `.objects` manager | `Rating.objects.filter()` |

---

## Code Patterns Introduced

### Complete Project Model
```python
class Project(models.Model):
    class Status(models.TextChoices):
        BANNED = "banned", "Banned"
        PENDING = "pending", "Pending"
        FINISHED = "finished", "Finished"
        CANCELED = "canceled", "Canceled"

    title = models.CharField(max_length=255)
    details = models.TextField()
    target = models.FloatField()
    current_money = models.FloatField(null=True)
    startdate = models.DateField()
    enddate = models.DateField()
    is_featured = models.BooleanField(default=False)

    # FK named without _id — Django creates category_id column automatically
    category = models.ForeignKey(
        'categories.Category',
        on_delete=models.PROTECT,  # blocks deletion if projects reference this category
        null=True
    )
    user = models.ForeignKey(
        'profiles.User',
        on_delete=models.PROTECT  # users are soft-deleted, never hard-deleted
    )
    tags = models.ManyToManyField('tags.Tag')  # Django manages junction table automatically

    status = models.CharField(
        max_length=20,
        choices=Status.choices,
        default=Status.PENDING
    )
    # avg_rate NOT stored here — derived field, computed in serializer via Avg aggregation
    created_at = models.DateTimeField(auto_now_add=True)
```

### Complete ProjectSerializer
```python
from rest_framework import serializers
from django.db.models import Avg
from .models import Project

class ProjectSerializer(serializers.ModelSerializer):
    # Flatten FK — source traverses the relation to get category name
    category = serializers.ReadOnlyField(source='category.name')

    # Computed fields — not on model, value comes from methods below
    user_fullname = serializers.SerializerMethodField()
    avg_rate = serializers.SerializerMethodField()

    class Meta:
        model = Project
        fields = '__all__'

    def get_user_fullname(self, obj):
        # obj is the Project instance — traverse to related User
        return f"{obj.user.first_name} {obj.user.last_name}"

    def get_avg_rate(self, obj):
        # aggregate() returns a dict: {"rate__avg": 4.2}
        result = obj.rating_set.aggregate(Avg("rate", default=0))
        return result["rate__avg"]
```

### URL Configuration Pattern
```python
# main urls.py
urlpatterns = [
    path('api/projects/', include('apps.projects.urls')),
]

# apps/projects/urls.py
router = DefaultRouter()
router.register(r"", ProjectViewSet)        # empty prefix — avoids api/projects/projects/
router.register(r"categories", CategoryViewSet)
router.register(r"tags", TagViewSet)

urlpatterns = [
    path("", include(router.urls)),
    path("home/", HomepageView.as_view(), name="homepage"),
    path("search/", ProjectSearchView.as_view(), name="project-search"),
    path("<int:pk>/similar/", SimilarProjectsView.as_view(), name="similar-projects"),
]
```

---

## References

| Topic | Link |
|---|---|
| Django Reusable Apps | https://docs.djangoproject.com/en/stable/intro/reusable-apps/ |
| AppConfig.name | https://docs.djangoproject.com/en/stable/ref/applications/#django.apps.AppConfig.name |
| Django on_delete | https://docs.djangoproject.com/en/stable/ref/models/fields/#django.db.models.ForeignKey.on_delete |
| Django RESTRICT | https://docs.djangoproject.com/en/stable/ref/models/fields/#django.db.models.RESTRICT |
| FK DB representation | https://docs.djangoproject.com/en/stable/ref/models/fields/#database-representation |
| Django TextChoices | https://docs.djangoproject.com/en/stable/ref/models/fields/#enumeration-types |
| Django ManyToManyField | https://docs.djangoproject.com/en/stable/ref/models/fields/#manytomanyfield |
| Django Aggregation | https://docs.djangoproject.com/en/stable/topics/db/aggregation/#avg |
| DRF SerializerMethodField | https://www.django-rest-framework.org/api-guide/fields/#serializermethodfield |
| DRF Routers | https://www.django-rest-framework.org/api-guide/routers/ |
| django-extensions | https://django-extensions.readthedocs.io/en/latest/ |
| Docker image prune | https://docs.docker.com/engine/reference/commandline/image_prune/ |
| Docker Compose exec | https://docs.docker.com/engine/reference/commandline/compose_exec/ |
| pip-tools | https://pip-tools.readthedocs.io/en/latest/ |
| Django migrations | https://docs.djangoproject.com/en/stable/topics/migrations/ |



prefetch related many to many releation ship to prevent N+1 querey

For many-to-many relationships set() accepts a list of either model instances or field values, normally primary keys, as the objs argument.


# Django Rest Framework: Project Images API Guide

## 1. Architectural Shift: Nested Resources
Moving images to a separate endpoint (`/projects/:id/images/`) is superior to a monolithic serializer because it provides granular control over individual files without re-uploading the entire set.

### Recommended URL Structure
```python
path('projects/<int:project_id>/images/', ProjectImageListView.as_view(), name='project-image-list'),
path('projects/<int:project_id>/images/<int:pk>/', ProjectImageDetailView.as_view(), name='project-image-detail'),
```

---

## 2. Key Pitfalls & Solutions

### Pitfall: Using `bulk_create` for Files
* **The Bug:** `Image.objects.bulk_create()` skips the model's `.save()` method and Django signals.
* **The Result:** Files are never sent to Cloudinary/S3; the database saves a path to a file that doesn't exist on the server.
* **The Fix:** Use a standard loop with `.create()` to trigger the storage backend.

### Pitfall: Reverse Relationship Lookups
* **The Bug:** `Project` does not have an `images` field; the `Image` model has the `ForeignKey`.
* **The Result:** `source='images'` in a serializer will fail.
* **The Fix:** Use `source='image_set'` (Django default) or define `related_name='images'` on the `Image` model ForeignKey.

### Pitfall: Security in Deletion
* **The Bug:** Deleting by `pk` alone allows users to delete images from other projects by guessing IDs.
* **The Fix:** Override `get_queryset` to filter by the `project_id` from the URL.

---

## 3. Implementation Reference

### The List/Create View
We override `create` specifically to support multiple file uploads (`getlist`) in a single request, which the default Generic view does not support.

```python
class ProjectImageListView(generics.ListCreateAPIView):
    serializer_class = ImageSerializer

    def get_queryset(self):
        return Image.objects.filter(project_id=self.kwargs['project_id'])

    def create(self, request, *args, **kwargs):
        files = request.FILES.getlist('path') # 'path' must match frontend key
        project = generics.get_object_or_404(Project, id=self.kwargs['project_id'])
        
        created_instances = []
        for f in files:
            # .create() ensures the file is actually uploaded to Cloudinary
            obj = Image.objects.create(project=project, path=f)
            created_instances.append(obj)
        
        serializer = self.get_serializer(created_instances, many=True)
        return Response(serializer.data, status=status.HTTP_201_CREATED)
```

### The Delete View
Using `DestroyAPIView` is preferred over `APIView` for single-instance deletion as it handles the logic automatically.

```python
class ProjectImageDetailView(generics.DestroyAPIView):
    serializer_class = ImageSerializer

    def get_queryset(self):
        # Enforces that the image must belong to the project in the URL
        return Image.objects.filter(project_id=self.kwargs['project_id'])
```

---

## 4. Glossary of Concepts
* **`generics`**: DRF's toolkit of pre-built views (templates) for standard CRUD actions.
* **`get_object_or_404`**: A safety fetch. It returns the object if found, otherwise it sends a clean JSON 404 response to the client.
* **`request.FILES.getlist(key)`**: Essential for multiple file uploads; it retrieves all files associated with a single key as a Python list.

# Session Summary — 2026-04-17 — Django DRF Serializers & M2M Relationships

## What We Covered
Built out a `ProjectSerializer` in Django REST Framework covering `create` and `update` methods, handling ManyToMany relationships for tags, multiple image uploads via Cloudinary, and debugged several real errors along the way. Finished with an architectural discussion on dedicated image endpoints.

---

## Key Concepts Learned

- **List Comprehensions**
  - What it is: Python's syntax for transforming an iterable into a list in one line — equivalent to `.map()` in JavaScript
  - Why it matters: Cleaner, more Pythonic than a for loop when building lists
  - Doc: [Python List Comprehensions](https://docs.python.org/3/tutorial/datastructures.html#list-comprehensions)

- **ListField (DRF)**
  - What it is: A DRF serializer field that validates a list of items, each validated against a `child` field type
  - Why it matters: Lets you accept arrays of simple values (strings, ints) in API input without touching the DB
  - Doc: [DRF ListField](https://www.django-rest-framework.org/api-guide/fields/#listfield)

- **ListField vs PrimaryKeyRelatedField**
  - `ListField` — validates shape/type only, no DB queries
  - `PrimaryKeyRelatedField(many=True)` — validates PKs exist in the DB, talks to the DB
  - Doc: [PrimaryKeyRelatedField](https://www.django-rest-framework.org/api-guide/relations/#primarykeyrelatedfield)

- **bulk_create limitations**
  - What it is: A Django ORM method for inserting multiple records in a single SQL query
  - Why it matters: Does **not** work with ManyToMany relationships — it bypasses the M2M junction table
  - Doc: [bulk_create](https://docs.djangoproject.com/en/5.2/ref/models/querysets/#bulk-create)

- **get_or_create**
  - What it is: Fetches an object matching the given kwargs, or creates it if it doesn't exist. Returns a `(object, created)` tuple
  - Why it matters: Prevents duplicate DB entries and handles M2M tag creation gracefully
  - Doc: [get_or_create](https://docs.djangoproject.com/en/5.2/ref/models/querysets/#get-or-create)

- **RelatedManager.set()**
  - What it is: Replaces the entire set of M2M related objects in one call — removes old, adds new
  - Why it matters: Cleanest way to do a full replace on a M2M relationship
  - Doc: [RelatedManager.set()](https://docs.djangoproject.com/en/5.2/ref/models/relations/#django.db.models.fields.related.RelatedManager.set)

- **setattr() for dynamic updates**
  - What it is: Python built-in that sets an attribute on an object dynamically by name
  - Why it matters: Lets you loop over `validated_data` and update all plain fields without hardcoding each one
  - Doc: [setattr](https://docs.python.org/3/library/functions.html#setattr)

- **extra_kwargs scoping**
  - What it is: `extra_kwargs` in `Meta` only applies to fields Django auto-generates from the model
  - Why it matters: If you declare a field explicitly on the serializer, `extra_kwargs` for that field is silently ignored — you must configure it directly on the field declaration
  - Doc: [DRF ModelSerializer extra_kwargs](https://www.django-rest-framework.org/api-guide/serializers/#additional-keyword-arguments)

- **FieldFile.delete()**
  - What it is: Deletes the actual file from storage (Cloudinary in this case)
  - Why it matters: Deleting a DB record does not delete the file from storage — you must do both explicitly
  - Doc: [FieldFile.delete()](https://docs.djangoproject.com/en/5.2/ref/models/fields/#django.db.models.fields.files.FieldFile.delete)

- **PUT vs PATCH in DRF**
  - `PUT` — full replace, all fields expected
  - `PATCH` — partial update, sets `partial=True` on the serializer, missing fields are skipped
  - Doc: [Partial Updates](https://www.django-rest-framework.org/api-guide/serializers/#partial-updates)

---

## Problems We Worked Through

1. **`ManyRelatedManager` not iterable (first occurrence)**
   - Cause: `bulk_create` does not work with M2M relationships
   - Fix: Replaced `bulk_create` + `.set()` with `get_or_create` per tag + `.add()`

2. **`add() got unexpected keyword argument 'bulk'`**
   - Cause: `bulk` argument does not exist on M2M `add()` — only on reverse FK managers
   - Fix: Removed `bulk=True` from `.add()` call

3. **`ManyRelatedManager` not iterable (second occurrence)**
   - Cause: `extra_kwargs` `write_only=True` was being ignored because `tags` was explicitly declared on the serializer. DRF was trying to serialize `tags` as a `ListField` against a M2M manager on the response
   - Fix: Moved `write_only=True` and `required=False` directly into the `ListField` declaration, removed from `extra_kwargs`

4. **`value too long for type character varying(100)`**
   - Cause: `ImageField` defaults to `max_length=100`, Cloudinary URLs exceed this
   - Fix: Added explicit `max_length` to the `path` field on the `Image` model

---

## Code Patterns Introduced

### create() with M2M and file uploads
```python
def create(self, validated_data):
    images_data = validated_data.pop('images', [])
    tags_data = validated_data.pop('tags', [])
    
    project = Project.objects.create(**validated_data)
    
    if tags_data:
        # get_or_create prevents duplicate tags, [0] unpacks the (object, created) tuple
        tag_instances = [Tag.objects.get_or_create(name=tag)[0] for tag in tags_data]
        project.tags.add(*tag_instances)  # no bulk= for M2M
    
    if images_data:
        image_instances = [Image(path=img, project=project) for img in images_data]
        Image.objects.bulk_create(image_instances)  # fine here — no M2M involved
    
    return project
```

### update() with dynamic setattr loop
```python
def update(self, instance, validated_data):
    images_data = validated_data.pop('images', None)
    tags_data = validated_data.pop('tags', None)

    # pop M2M/relational fields first — setattr can't handle them
    for key, data in validated_data.items():
        setattr(instance, key, data)
    instance.save()

    if tags_data:
        tag_instances = [Tag.objects.get_or_create(name=tag)[0] for tag in tags_data]
        instance.tags.set(tag_instances)  # replaces entire tag set

    if images_data:
        # delete files from Cloudinary first, then delete DB records
        existing_images = instance.image_set.all()
        for img in existing_images:
            img.path.delete()
        existing_images.delete()
        image_instances = [Image(path=img, project=instance) for img in images_data]
        Image.objects.bulk_create(image_instances)

    return instance
```

### Explicit field declaration overrides extra_kwargs
```python
# WRONG — extra_kwargs ignored because tags is explicitly declared
tags = serializers.ListField(child=serializers.CharField(max_length=255))
extra_kwargs = { "tags": {"write_only": True} }  # silently ignored

# CORRECT — configure directly on the field
tags = serializers.ListField(
    child=serializers.CharField(max_length=255),
    write_only=True,
    required=False
)
```

---

## Architecture Note

Image add/delete operations should be handled via **dedicated endpoints** rather than embedded in the project update:
- `POST /api/projects/{id}/images/` — add images
- `DELETE /api/projects/{id}/images/{image_id}/` — delete a specific image

This avoids mixed input types (URLs vs files) and follows REST conventions.

Doc: [DRF Routers](https://www.django-rest-framework.org/api-guide/routers/)

---

## References

- [Python List Comprehensions](https://docs.python.org/3/tutorial/datastructures.html#list-comprehensions)
- [PEP 8 — Programming Recommendations](https://peps.python.org/pep-0008/#programming-recommendations)
- [DRF ListField](https://www.django-rest-framework.org/api-guide/fields/#listfield)
- [DRF Core field arguments — required](https://www.django-rest-framework.org/api-guide/fields/#required)
- [DRF PrimaryKeyRelatedField](https://www.django-rest-framework.org/api-guide/relations/#primarykeyrelatedfield)
- [DRF ModelSerializer extra_kwargs](https://www.django-rest-framework.org/api-guide/serializers/#additional-keyword-arguments)
- [DRF Partial Updates](https://www.django-rest-framework.org/api-guide/serializers/#partial-updates)
- [DRF Routers](https://www.django-rest-framework.org/api-guide/routers/)
- [Django bulk_create](https://docs.djangoproject.com/en/5.2/ref/models/querysets/#bulk-create)
- [Django get_or_create](https://docs.djangoproject.com/en/5.2/ref/models/querysets/#get-or-create)
- [Django RelatedManager.set()](https://docs.djangoproject.com/en/5.2/ref/models/relations/#django.db.models.fields.related.RelatedManager.set)
- [Django RelatedManager.add()](https://docs.djangoproject.com/en/5.2/ref/models/relations/#django.db.models.fields.related.RelatedManager.add)
- [Django FieldFile.delete()](https://docs.djangoproject.com/en/5.2/ref/models/fields/#django.db.models.fields.files.FieldFile.delete)
- [Django ImageField](https://docs.djangoproject.com/en/5.2/ref/models/fields/#imagefield)
- [setattr — Python built-ins](https://docs.python.org/3/library/functions.html#setattr)


## Session Wrap-Up: Django Optimization & Serializer Logic

In this session, we optimized the **WyrmHole** bookstore API by implementing advanced queryset techniques and resolving serialization errors. Below is the summary of the key concepts and fixes we implemented.

---

### 1. Database Optimization
We focused on moving heavy calculations and relationship lookups from the Serializer (Python) to the ViewSet (Database) to avoid the **N+1 problem**.

* **`select_related`**: Used for **Single-Value** relationships (Foreign Key to User/Category). It uses a SQL `JOIN` to fetch data in one query.
* **`prefetch_related`**: Used for **Multi-Value** relationships (Tags, Images). It runs a separate query and maps the results in memory to avoid redundant data.
* **`annotate`**: Used to calculate values like `avg_rate` at the database level using `Avg()`.
* **`__` (Double Underscore)**: Acts as a **path connector** to reach fields in related tables (e.g., `ratings__stars`).

### 2. ViewSet Architecture
We addressed the requirements for `ModelViewSet` to ensure proper routing and efficiency.

* **`get_queryset()` vs `queryset`**:
    * Using the `queryset` variable is clean for static optimizations.
    * Overriding `get_queryset()` is necessary for dynamic logic (like filtering by `request.user`).
* **The `basename` Requirement**: If the `queryset` attribute is removed, you must specify a `basename` in your `urls.py` router registration to help DRF name the URL patterns.

### 3. Debugging & Error Resolution
We walked through several common Django errors encountered during the implementation:

* **`NoneType` has no len()**: Occurs when `get_queryset()` lacks a `return` statement.
* **`ImproperlyConfigured` (Invalid Field)**: Happens when a Serializer tries to include an annotated field (like `avg_rate`) that isn't explicitly defined in the Serializer class. 
    * *Fix:* Define `avg_rate = serializers.FloatField(read_only=True)`.
* **`FieldError` (Cannot resolve keyword)**: Occurs when the string passed to `Avg()` or `filter()` doesn't match the model's field name or `related_name`.

### 4. Final Implementation Patterns
For a clean, "no-fluff" response, we established the following pattern for your `Project` models:

**The ViewSet Logic:**
```python
def get_queryset(self):
    return Project.objects.annotate(
        avg_rate=Coalesce(Avg('ratings__stars'), Value(0.0))
    ).select_related('user', 'category'
    ).prefetch_related('tags', 'image_set')
```

**The Serializer Logic:**
```python
class ProjectSerializer(serializers.ModelSerializer):
    avg_rate = serializers.FloatField(read_only=True)
    images_urls = ImageSerializer(many=True, read_only=True, source='image_set')
    # ... other fields
```

