# Федоров, Д. Ю. Кибернетический подход к управлению процессом обучения на основе семантических сетей знаний [Текст] / Д.Ю. Федоров. – СПб. : Изд-во Политехн. ун-та, 2016. – 40 с.
# http://dfedorov.spb.ru/monografya_Fedorov.pdf

import random # генератор случайного времени

# теория систем - main
'''
l_names = ['Дерево свойств',
'Интегративные свойства',
'Качество',
'Объект',
'Поведение',
'Подсистема',
'Развитие',
'Свойство',
'Связь',
'Система',
'Ситуация',
'Состояние',
'Среда',
'Структура',
'Управление',
'Функционирование',
'Характеристика',
'Целое',
'Цель',
'Элемент']

M = [[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
     [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
     [0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
     [0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1],
     [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
     [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
     [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
     [1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0],
     [0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
     [0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0],
     [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0],
     [0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
     [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
     [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
     [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
     [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0],
     [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
     [0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
     [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
     [0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0]]

'''
# теория систем
'''
l_names = ['Объект',
 'Связь',
 'Характеристика',
 'Целое',
 'Поведение',
 'Функционирование',
 'Структура',
 'Ситуация',
 'Развитие',
 'Элемент',
 'Состояние',
 'Качество',
 'Среда',
 'Свойство',
 'Подсистема',
 'Управление',
 'Цель',
 'Интегративные свойства',
 'Дерево свойств',
 'Система']
        

M = [[0,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,0,0],
     [0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1],
     [0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0],
     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0],
     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0],
     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0],
     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0],
     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
     [0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,1],
     [0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0],
     [0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0],
     [0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0],
     [0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0],
     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0],
     [0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
     [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
     [0,0,0,0,0,1,1,1,0,0,0,0,1,0,1,1,1,0,1,0]]
'''
'''
l_names = ["Вещественное число", "Идентификатор", "Интерпретатор", "Ключевое слово", "Компилятор", "Логический тип", "Машинный язык", 
"Описание", "Подпрограмма", "Тип данных", "Транслятор", "Язык высокого уровня", "Программа", "Язык программирования"]

M = [[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0], [0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0], [0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1], [0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0]]
'''


# ПАСЗИ
l_names = ["Точка останова", "Дизассемблер", "Ассемблер", "Машинный код", "Язык ассемблера", "Отладчик"] 

M = [[0, 0, 0, 0, 0, 0],[0, 0, 0, 0, 0, 1],[0, 0, 0, 0, 0, 0],[0, 1, 1, 0, 1, 1],[0, 1, 1, 0, 0, 0],[1, 0, 0, 0, 0, 0]]


# список терминов
l_terms = []
# рабочая память
l_now = []
# изученные понятия (добавленные в траекторию обучения) 
l_learn = []
# пропущенные понятия (добавить в траекторию позже)
l_later = []

class Term():
    name = ""    
    def __init__ (self, newName, gentime):
        self.name = newName
        self.time = gentime # время на изучение теор.части понятия (лекция)
        # http://stackoverflow.com/questions/14178203/python-object-containing-an-array-of-objects-being-weird
        self.l_in = [] # входные связи
        self.l_out = [] # выходные связи
        self.l_lab = [] # лаб.работы        
        self.l_pr = [] # практ.работы
    def add_lin (self, term):
        self.l_in.append(term)
    def add_lout (self, term):
        self.l_out.append(term)
    def getName(self):
        return self.name
    def add_lab(self, lab):
        self.l_lab.append(lab)
    def add_pr(self, pr):
        self.l_pr.append(pr)
    def getTime(self):
        return self.time

class LLR():
    about=""    
    def __init__ (self, newAbout, gentime):
        self.about = newAbout
        self.time = gentime # время на выполнение ЛР или ПЗ
    def getAbout(self):
        return self.about
    def getTime(self):
        return self.time

#class Student():
	


# заполнить массив элементами класса Term
for i in range(len(l_names)):    
    l_terms.append(Term (l_names[i], random.randint(20,100)))    

#for i in l_terms:
#    print(i.getName())

# формирование списка входных и выходных связей для каждого термина на основе матрицы инцидентности
for i in range (len(M)):
    k = 0
    for j in M[i]:
        if j == 1:
            # записать ссылку на объект
            l_terms[i].add_lout(l_terms[k])
            #print(i, k, l_terms[k].getName())
        k += 1

for i in range (len(M)):
    k = 0
    for j in M:
        if j[i] == 1:
            l_terms[i].add_lin(l_terms[k]) 
            #print(i, k, l_terms[k].getName())
        k += 1

# в этот момент анализируем связи между понятиями:

for i in l_terms:
    for j in i.l_in:
        i.add_lab(LLR(j.getName(), random.randint(20, 100)))
        i.add_pr(LLR(j.getName(), random.randint(20, 100)))

# проверка
print("ИП:")
for i in l_terms:
    print("Термин:", i.getName())
    for j in i.l_lab:
        print("ЛР:", j.getAbout())
    for k in i.l_pr:
        print("ПЗ:", k.getAbout())
 
for i in l_terms:
    if not i.l_in:
        # добавили понятие нулевого уровня в изученные
        l_learn.append(i)
        # добавили выходные понятия в рабочую память
        l_now.extend(i.l_out)

# проверка
print("\nНулевой уровень:")
for ll in l_learn:
    print(ll.getName()) 
print("\nТекущие понятия:")        
for ll in l_now:
    print(ll.getName()) 

print("")
'''
if set(l_learn) >= set(l_now[2].l_in):
    l_learn.append(l_now[2])
    l_now.extend(l_now[2].l_out)
    print("1", l_now[2].getName())
else:
    l_later.append(l_now[2])
    print("2", l_now[2].getName())
'''

while l_now:   
    #print(l_now.pop(0).getName())
    #tmp = set(l_now.pop(0).l_in)
    tmp = l_now.pop(0)
    if set(l_learn) >= set(tmp.l_in):
        if not (tmp in l_learn):
            l_learn.append(tmp)
            l_now.extend(tmp.l_out)
        #print("1", tmp.getName())
    else:
        l_later.append(tmp)
        #print("2", tmp.getName())    

print("Завершение работы:")
print("\nl_now:")
for i in l_now:
    print(i.getName())

print("\nl_learn:")
kk = 0
for i in l_learn:    
    print(kk, i.getName())
    kk += 1

print("\nl_later:")
for i in l_later:
    print(i.getName())

# проверяем l_later
# если элемент встречается в l_learn - удаляем его
# иначе - ???

print("\nПросмотр отложенных понятий: ")
while l_later:
    tmp = l_later.pop(0)
    if tmp in l_learn:
        print("изучен", tmp.getName())
    else:
        print("паника!", tmp.getName())

'''
print("\nТраектория обучения:")
jj=0
for i in l_learn:    
    print(jj,") ",i.getName(), " , время: ", i.getTime(), sep='')
    #print("->", end=" ")
    jj+=1
    
# траектория с учетом ПЗ:
jj=0
print("\n\nТраектория обучения с учетом ПЗ:")
for i in l_learn:    
    print(jj, ") ", "Л (", i.getName(), ")", " , время: ", i.getTime(), sep='')
    #print("->", end=" ")
    jj+=1
    for j in i.l_pr:
        print(jj, ") ", "ПЗ (", j.getAbout(), ")", " , время: ", j.getTime(), sep='')
        #print("->", end=" ")
        jj+=1
    
# траектория с учетом ЛР:
jj = 0
print("\n\nТраектория обучения с учетом ЛР:")
for i in l_learn:    
    for j in i.l_lab:
        print(jj, ") ", "ЛР (", j.getAbout(), ")"," , время: ", j.getTime(), sep='')
        #print("->", end=" ")
        jj+=1
    print(jj, ") ", "Л (", i.getName(), ")", " , время: ", i.getTime(), sep='')
    #print("->", end=" ")
    jj+=1
'''

##################################################################
#                 траектория с учетом времени                    #
##################################################################

print("\nТраектория обучения:")
jj=0
sum_time = 0
flag = 0
for i in l_learn:    
    print(jj,") ",i.getName(), " , время: ", i.getTime(), sep='')
    sum_time += i.getTime()
    jj+=1
    if sum_time > 1024 and not flag: # в семестре 200 минут
         print("затрачено времени: ", sum_time, "Следующий модуль")
         flag = 1
print("Общее время: ", sum_time)


# траектория с учетом ПЗ:
jj=0
sum_time = 0
flag = 0
print("\n\nТраектория обучения с учетом ПЗ:")
for i in l_learn:    
    print(jj, ") ", "Л (", i.getName(), ")", " , время: ", i.getTime(), sep='')
    #print("->", end=" ")
    jj+=1
    for j in i.l_pr:
        print(jj, ") ", "ПЗ (", j.getAbout(), ")", " , время: ", j.getTime(), sep='')
        #print("->", end=" ")
        jj+=1
        sum_time = sum_time + i.getTime() + j.getTime()
    if sum_time > 1024 and not flag:    
        print("затрачено времени: ", sum_time, "Следующий модуль")
        flag = 1
print("Общее время: ", sum_time)


# траектория с учетом ЛР:
jj = 0
sum_time = 0
flag = 0
print("\n\nТраектория обучения с учетом ЛР:")
for i in l_learn:    
    for j in i.l_lab:
        print(jj, ") ", "ЛР (", j.getAbout(), ")"," , время: ", j.getTime(), sep='')
        #print("->", end=" ")
        jj+=1
        sum_time += j.getTime()
    print(jj, ") ", "Л (", i.getName(), ")", " , время: ", i.getTime(), sep='')
    #print("->", end=" ")
    jj+=1
    sum_time += i.getTime()
    if sum_time > 1024 and not flag:    
        print("затрачено времени: ", sum_time, "Следующий модуль")
        flag = 1
print("Общее время: ", sum_time)    




