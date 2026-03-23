class Human:
    country = 'Egypt'

    def __init__(self, name):
        self.name = name
        print(f"A human named {self.name} is created")

man = Human('iti-2026')
man.name = 'ahmed'
man2 = Human('iti-2027')
print(man.name)
print(man2.name)
print(man.country, man2.country)
man.country = 'KSA'
Human.country = 'USA'
print(man.country, man2.country)

