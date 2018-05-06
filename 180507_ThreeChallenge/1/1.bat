:::::::查看所有子网IP.bat:::::::
@echo off
::取消回显机制
title 查看所有子网IP
set /a Online=0
set /a Offline=0
set /a Total=256
:: 数值变量赋值
set StartTime=%time%
:: 记录程序的开始时间，time为保留字符
for /f "delims=: tokens=2" %%i in ('ipconfig /all ^| find /i "IPv4 地址"') do set IP=%%i
:: 获得本机IP
if "%IP%"=="" echo 未连接到网络 & pause & goto EOF
if "%IP%"==" 0.0.0.0" echo 未连接到网络 & pause & goto EOF
echo 本机IP：%IP%
:: 当IP为空或 0.0.0.0 时，提示未连接并退出该程序
:: 使用for语句分割字符串
for /f "delims=. tokens=1,2,3,4" %%i in ("%IP%") do (
  set /a IP1=%%i
  set /a IP2=%%j
  set /a IP3=%%k
  set IP4str=%%l
)
for /f "delims=(" %%i in ("%IP4str%") do (
  set /a IP4=%%i
)
:: 以句点为分隔符，分别将IP的四个十进制数赋给四个变量
set /a IP4=0
echo 在线的IP：
:: 初始化IP的第四个数值为零
:RETRY
ping %IP1%.%IP2%.%IP3%.%IP4% -n 1 -w 200 -l 16>nul && set /a Online+=1 && echo %IP1%.%IP2%.%IP3%.%IP4% || set /a Offline+=1
:: ping 目标IP
set /a Scanned=%Online%+%Offline%
set /a Progress=(%Online%+%Offline%)*100/%Total%
echo 正在扫描：%Scanned%/%Total% 扫描进度：%Progress%%%
:: 删除当前行的内容，并重新显示进度信息
set /a IP4+=1
if %IP4% lss %Total% goto :RETRY
:: 当IP的第四个数值小于总数时，跳转回 :RETRY 处，重复执行直到全部 ping 完为止
echo.
echo.
set EndTime=%time%
:: 记录程序的结束时间
set /a Seconds = %EndTime:~6,2% - %StartTime:~6,2%
set /a Minutes = %EndTime:~3,2% - %StartTime:~3,2%
if %Seconds% lss 0 set /a Seconds += 60 & set /a Minutes -= 1
if %Minutes% lss 0 set /a Minutes += 60
:: 计算时间差
set /a Percent=%Online%*100/(%Online%+%Offline%)
:: 计算在线百分比
echo 在线IP个数（不包含本机IP）:  %Online%
echo 不在线IP个数: %Offline%
echo 在线百分比:  %Percent%%%
echo 统计耗时:   %Minutes%分%Seconds%秒
echo 统计日期:   %date% %time:~0,-3%
pause