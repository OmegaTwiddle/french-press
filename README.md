french-press
============

Java .class file interpreter


How to run
===========

  To run, simply do:

    1. gcc java_class_reader.c 
    2. ./a.out A.class

  Note, A.class is a java class file, which you can generate as follows:
  
    1. echo "public class A { public void method1(){} } " >> A.java
    2. javac A.class


