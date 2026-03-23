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

[notice] A new release of pip is available: 25.3 -> 26.0.1
[notice] To update, run: pip install --upgrade pip

python manage.py startapp your_app_name
python magange.py makemigrations
python manage.py migrate