close all;
clear all;
clc;

pathData = 'C:\FilesBack\NPeleng\ResultFile\'; % ���� � ����� � ��������� ��������� � ��������� ������
fileNameXMas = 'Xobj.txt';    % �������� ���������� ����� � �������� ��������� x
fileNameYMas = 'Yobj.txt';    % �������� ���������� ����� � �������� ��������� y

fileNameXMasN = 'Xnab.txt';    % �������� ���������� ����� � �������� ��������� x
fileNameYMasN = 'Ynab.txt';    % �������� ���������� ����� � �������� ��������� y

pathGraph = 'C:\FilesBack\NPeleng\ResultFile\';         % ����, ���� ����� ��������� ����������� ����������� ��������
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

%plot(xMas, yMas, 'or', 'MarkerSize',8, xMasN, yMasN, 'r', 'MarkerSize',8 );   % ������ 1 - ���������-��������
%plot(xMas, yMas, '-k', 'LineWidth', 1 ,xMasN, yMasN, '-k', 'LineWidth', 1 );   % ������ 2 - ������


figure(1);
hold on;
%plot(xMas, yMas, 'or', xMasN, yMasN, 'r' );   % ������ 1 - ���������-��������
plot(xMas, yMas,'--rs',...
    'LineWidth',2,...
    'MarkerSize',10,...            % ������ �������� 
    'MarkerEdgeColor','b',...      % ���� 
    'MarkerFaceColor',[0.7,0.2,0.2])
plot(xMasN, yMasN,'--ks',...
    'LineWidth',2,...
    'MarkerSize',10,...            % ������ �������� 
    'MarkerEdgeColor','y',...      % ���� 
    'MarkerFaceColor',[0,0,0]);
title = title('�������� ������� � �����������');                % �������� 
xlabel( '��������� �� ��� x' );              % ������� � ��� x
ylabel( '��������� �� ��� y' );              % ������� � ��� y
grid on;                                  % ��������� �����
grid minor;                               % ��������� ����� � ������ �����
hold off;                                  % ����� ��������� ��� ���� ������
%plot(xMas, yMas, '-k',xMasN, yMasN, '-b'  );   % ������ 2 - ������
xlim([-2500, 15000]); % ����� ������ ������ ������� ������� ����������� ��������
ylim([-2500, 15000]);
legend( ...
    '��������� ������� �� ������ ���� �������������', ...
    '���������� �����������', ...
    '��������� ����������� �� ������ ���� ������������� ', ...
    'location', 'northwest');             % ������� � ��������


saveas(gcf,[pathGraph, fileNameToSave]);  % ��������� ��� ��������



