# Physical Computing Project 2026 - IT KMITL

## HOPIT
เกมกระโดดหลบสิ่งกีดขวางโดยใช้ sensor เป็นตัวส่งสัญญาณ ทำให้เกมเป็นแบบ touchless ที่ไม่เป็นจำเป็นต้องสัมผัส

## Website

## Clip VDO

## อุปกรณ์
> - Arduino R4 UNO WIFI
> - Ultrasonic Distance (4 PIN)
> - Breadboard Mini
> - LCD 16x2 (I2C)

## Library
> - LiquidCrystal_I2C.h : ใช้ควบคุมจอแสดงผล LCD (Liquid Crystal Display) ผ่านระบบสื่อสารแบบ I2C
> - Wire.h : ใช้สำหรับควบคุมการสื่อสารข้อมูลแบบ I2C

## การทำงาน
- Input : รับข้อมูลจากการโบกมือผ่าน sensor โดยใช้ Ultrasonic Distance ในระยะ 2-15 ซม.
- Output : แสดงหน้าจอ LCD ที่มีตัวละครปละกระโดดหลบสิ่งกีดขวางที่สุ่มโผล่มาตามจังหวะที่ผู้เล่นโบกมือผ่าน sensor

## รูปภาพ 


## สมาชิกกลุ่ม
> - 68070089 นิรัชพล กลิ่นขจร
> - 68070017 จีรวรรณ น่วมขยัน
> - 68070032 ญาณิศา จันทร์อุดม
> - 68070078 นภัทร อยู่เจริญ
> - 68070079 นภัสวรรณ เกิดแก้ว
