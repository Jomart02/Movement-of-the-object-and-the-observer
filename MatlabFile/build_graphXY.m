close all;
clear all;
clc;

pathData = 'C:\FilesBack\NPeleng_PK\'; % ���� � ����� � ��������� ��������� � ��������� ������
fileNameXMas = 'Xobj.txt';    % �������� ���������� ����� � �������� ��������� x
fileNameYMas = 'Yobj.txt';    % �������� ���������� ����� � �������� ��������� y

fileNameXMasN = 'Xnab.txt';    % �������� ���������� ����� � �������� ��������� x
fileNameYMasN = 'Ynab.txt';    % �������� ���������� ����� � �������� ��������� y

pathGraph = 'C:\FilesBack\NPeleng_PK\';         % ����, ���� ����� ��������� ����������� ����������� ��������
fileNameToSave = 'graph.bmp'; % ��� ����� ��� ������� ����������� ����������� � ���������

%=========================================================================
% ������ �������� ��������� �� ��������� ������
%=========================================================================
F = fopen([pathData, fileNameXMas], 'r'); % ������� ���� � ������ fileNameXMas �� ���� pathData
xMas = fscanf(F, '%f');                   % ��������� ������ ��������� �� ����� � xMas
fclose(F);                                % ������� ����

F = fopen([pathData, fileNameYMas], 'r');
yMas = fscanf(F, '%f');
fclose(F);

F = fopen([pathData, fileNameXMasN], 'r');
xMasN = fscanf(F, '%f');
fclose(F);

F = fopen([pathData, fileNameYMasN], 'r');
yMasN = fscanf(F, '%f');
fclose(F);

% ����������, ��� ����������� �� ��������
xMas
yMas
xMasN
yMasN

%=========================================================================
% ���������� ��������
%=========================================================================

figure(1);
hold on;
plot(xMas, yMas, 'or', xMasN, yMasN, 'og' );   % ������ 1 - ���������-��������
title = title('�������� �������');                % �������� 
xlabel( '��������� �� ��� x' );              % ������� � ��� x
ylabel( '��������� �� ��� y' );              % ������� � ��� y
grid on;                                  % ��������� �����
grid minor;                               % ��������� ����� � ������ �����                                % ����� ��������� ��� ���� ������
plot(xMas, yMas, '-k',xMasN, yMasN, '-b'  );   % ������ 2 - ������
hold off; 
xlim([-5000, 15000]); % ����� ������ ������ ������� ������� ����������� ��������
ylim([-2500, 15000]);
legend( ...
    '��������� ������� �� ������ ���� �������������', ...
    '��������� ����������� �� ������ ���� �������������', ...
    '���������� ������� ', ...
    '���������� ����������� ', ...
    'location', 'northwest');             % ������� � ��������


saveas(gcf,[pathGraph, fileNameToSave]);  % ��������� ��� ��������



