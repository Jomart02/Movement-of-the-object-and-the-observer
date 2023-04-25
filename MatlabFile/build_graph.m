close all;
clear all;
clc;

pathData = 'C:\FilesBack\NPeleng\ResultFile\'; % путь к папке с массивами координат в текстовых файлах
fileNameXMas = 'Xobj.txt';    % название текстового файла с массивом координат x
fileNameYMas = 'Yobj.txt';    % название текстового файла с массивом координат y

fileNameXMasN = 'Xnab.txt';    % название текстового файла с массивом координат x
fileNameYMasN = 'Ynab.txt';    % название текстового файла с массивом координат y

pathGraph = 'C:\FilesBack\NPeleng\ResultFile\';         % путь, куда нужно сохранить изображения построенных графиков
fileNameToSave = 'graph.bmp'; % имя файла под которым сохраняется изображение с графиками

%=========================================================================
% Чтение массивов координат из текстовых файлов
%=========================================================================
F = fopen([pathData, fileNameXMas], 'r'); % открыть файл с именем fileNameXMas по пути pathData
xMas = fscanf(F, '%f');                   % прочитать массив координат из файла в xMas
fclose(F);                                % закрыть файл

F = fopen([pathData, fileNameYMas], 'r');
yMas = fscanf(F, '%f');
fclose(F);

F = fopen([pathData, fileNameXMasN], 'r');
xMasN = fscanf(F, '%f');
fclose(F);

F = fopen([pathData, fileNameYMasN], 'r');
yMasN = fscanf(F, '%f');
fclose(F);

% посмотреть, что прочиталось из массивов
xMas
yMas
xMasN
yMasN

%=========================================================================
% Построение графиков
%=========================================================================

%plot(xMas, yMas, 'or', 'MarkerSize',8, xMasN, yMasN, 'r', 'MarkerSize',8 );   % график 1 - маркерами-кружками
%plot(xMas, yMas, '-k', 'LineWidth', 1 ,xMasN, yMasN, '-k', 'LineWidth', 1 );   % график 2 - линией


figure(1);
hold on;
%plot(xMas, yMas, 'or', xMasN, yMasN, 'r' );   % график 1 - маркерами-кружками
plot(xMas, yMas,'--rs',...
    'LineWidth',2,...
    'MarkerSize',10,...            % размер маркеров 
    'MarkerEdgeColor','b',...      % цвет 
    'MarkerFaceColor',[0.7,0.2,0.2])
plot(xMasN, yMasN,'--ks',...
    'LineWidth',2,...
    'MarkerSize',10,...            % размер маркеров 
    'MarkerEdgeColor','y',...      % цвет 
    'MarkerFaceColor',[0,0,0]);
title = title('Движение объекта и наблюдателя');                % название 
xlabel( 'Положение по оси x' );              % подпись к оси x
ylabel( 'Положение по оси y' );              % подпись к оси y
grid on;                                  % включение сетки
grid minor;                               % включение сетки с мелким шагом
hold off;                                  % чтобы построить еще один график
%plot(xMas, yMas, '-k',xMasN, yMasN, '-b'  );   % график 2 - линией
xlim([-2500, 15000]); % чтобы самому задать пределы области отображения графиков
ylim([-2500, 15000]);
legend( ...
    'Положение объекта на каждом шаге моделирования', ...
    'Траектория наблюдателя', ...
    'Положение наблюдателя на каждом шаге моделирования ', ...
    'location', 'northwest');             % легенда к графикам


saveas(gcf,[pathGraph, fileNameToSave]);  % сохранить как картинку



