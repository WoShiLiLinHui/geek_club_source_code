:::::::�鿴��������IP.bat:::::::
@echo off
::ȡ�����Ի���
title �鿴��������IP
set /a Online=0
set /a Offline=0
set /a Total=256
:: ��ֵ������ֵ
set StartTime=%time%
:: ��¼����Ŀ�ʼʱ�䣬timeΪ�����ַ�
for /f "delims=: tokens=2" %%i in ('ipconfig /all ^| find /i "IPv4 ��ַ"') do set IP=%%i
:: ��ñ���IP
if "%IP%"=="" echo δ���ӵ����� & pause & goto EOF
if "%IP%"==" 0.0.0.0" echo δ���ӵ����� & pause & goto EOF
echo ����IP��%IP%
:: ��IPΪ�ջ� 0.0.0.0 ʱ����ʾδ���Ӳ��˳��ó���
:: ʹ��for���ָ��ַ���
for /f "delims=. tokens=1,2,3,4" %%i in ("%IP%") do (
  set /a IP1=%%i
  set /a IP2=%%j
  set /a IP3=%%k
  set IP4str=%%l
)
for /f "delims=(" %%i in ("%IP4str%") do (
  set /a IP4=%%i
)
:: �Ծ��Ϊ�ָ������ֱ�IP���ĸ�ʮ�����������ĸ�����
set /a IP4=0
echo ���ߵ�IP��
:: ��ʼ��IP�ĵ��ĸ���ֵΪ��
:RETRY
ping %IP1%.%IP2%.%IP3%.%IP4% -n 1 -w 200 -l 16>nul && set /a Online+=1 && echo %IP1%.%IP2%.%IP3%.%IP4% || set /a Offline+=1
:: ping Ŀ��IP
set /a Scanned=%Online%+%Offline%
set /a Progress=(%Online%+%Offline%)*100/%Total%
echo ����ɨ�裺%Scanned%/%Total% ɨ����ȣ�%Progress%%%
:: ɾ����ǰ�е����ݣ���������ʾ������Ϣ
set /a IP4+=1
if %IP4% lss %Total% goto :RETRY
:: ��IP�ĵ��ĸ���ֵС������ʱ����ת�� :RETRY �����ظ�ִ��ֱ��ȫ�� ping ��Ϊֹ
echo.
echo.
set EndTime=%time%
:: ��¼����Ľ���ʱ��
set /a Seconds = %EndTime:~6,2% - %StartTime:~6,2%
set /a Minutes = %EndTime:~3,2% - %StartTime:~3,2%
if %Seconds% lss 0 set /a Seconds += 60 & set /a Minutes -= 1
if %Minutes% lss 0 set /a Minutes += 60
:: ����ʱ���
set /a Percent=%Online%*100/(%Online%+%Offline%)
:: �������߰ٷֱ�
echo ����IP����������������IP��:  %Online%
echo ������IP����: %Offline%
echo ���߰ٷֱ�:  %Percent%%%
echo ͳ�ƺ�ʱ:   %Minutes%��%Seconds%��
echo ͳ������:   %date% %time:~0,-3%
pause