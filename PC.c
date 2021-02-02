typedef [context_handle] HANDLE RPC_HQUERY;//поддерживает инф-ию о вызываемых клиентом СП. Хэндл возвращает сервер, когда инициилизируется взаимодействие с клиентом для запроса данных СП. Клиент добавляет данные о СП в лист запроса, используя этот возвращенный хэндл. И когда клиент запрашивает значения СП, сервер знает из хэндла какие СП запрашивает клиент. Клиент закрывает хэндл при завершении запроса, позволяя серверу освободить ресурсы.

typedef RPC_HQUERY* PRPC_HQUERY;//указатель на хэндл



typedef struct _PERF_COUNTERSET_REG_INFO {
 GUID CounterSetGuid;			//Globally unique identifier уникально идентифицирующий counterset
 unsigned long CounterSetType;	//не используется, д.б. =0
 unsigned long DetailLevel;		//0x64 - СП создан для доступа обычными поль-ми, 0xC8 - СП создан для доступа админ-ми ИТ
 unsigned long NumCounters;		//Кол-во СП в counterset
 unsigned long InstanceType;	//0 - только одна инстанция у СП в counterset, 2 - много инстанций, 4 - глобальный агрегат, выполняет указанную в описании СП агрегацию, 6 - агрегат с несколькими экземплярами, выполняет операцию агрегирования по заданному набору счетчиков (например клиент может усреднить значение СП "А" из эксземпляров 1,2 и 5), C - история глобальной агрегации, выполняет операцию агрегирования по всем экземплярам, результат операции может быть кэширован поль-ем и использован в дальнейшем
} PERF_COUNTERSET_REG_INFO,
*PPERF_COUNTERSET_REG_INFO;



typedef struct _PERF_COUNTER_REG_INFO {
 unsigned long CounterId;		//Уникальный идентификатор в пределах CounterSet
 unsigned long Type;			//тип СП
 unsigned __int64 Attrib;		//атрибуты СП, бывают следующие: 1 - ссылка, запрос на сервере должен разыменовать счетчик для получения его значения(-ий), 2 - не показывать значение, 4 - без разделителей групп, т.е. заставляет данные СП отображать значение как одно число без запятых между цифрами, 8 - отображать как число Real, 10 - отображать в 16-ричной системе
 unsigned long DetailLevel;		//0x64 - СП создан для доступа обычными поль-ми, 0xC8 - СП создан для доступа админ-ми ИТ
 long DefaultScale;				//показывает значение на которое масштабируется значение СП, т.е. если значение СП 10 а DefaultScale=2, то посчитанное значение клиентом будет 1000
 unsigned long BaseCounterId;	//CounterId базового СП
 unsigned long PerfTimeId;		//CounterId другого СП чье значение используется для подсчета значение данного СП
 unsigned long PerfFreqId;		//CounterId другого СП чье значение частоты используется для подсчета значения данного СП
 unsigned long MultiId;			//CounterId другого СП чье значение используется для подсчета значения данного СП?
 unsigned long AggregateFunc;	//функции агрегации, если counterset относится к: global aggregate, multiple instance aggregate, global aggregate history. 0 - не определен, 1 - общее (сумма всех возвращенных значений инстанций СП), 2 - среднее, 3 - минимум, 4 - максимум
 unsigned long Reserved;		//зарезервировано, д.б. =0
} PERF_COUNTER_REG_INFO,		//
*PPERF_COUNTER_REG_INFO;		//


typedef struct _STRING_BUFFER_HEADER {	//структура, используется в начале блока заголовка СП
 DWORD dwSize; //общий размер возвращенных данных
 DWORD dwCounters;//кол-во СП в CounterSet
} PERF_STRING_BUFFER_HEADER,
*PPERF_STRING_BUFFER_HEADER;



typedef struct _STRING_COUNTER_HEADER {	//Структура, используемая в блоке заголовка СП
 DWORD dwCounterId; //CounterId СП
 DWORD dwOffset;	//сдвиг от конца набора структур _STRING_COUNTER_HEADER которым эта структра принадлежит, до соответствующего имени или описания
} PERF_STRING_COUNTER_HEADER,



typedef struct _PERF_INSTANCE_HEADER {//Используется в начале блок инстанции
 unsigned long Size;		//размер структуры в байтах и имени инстанции
 unsigned long InstanceId;	//Идентификатор инстнации, каждая активная инстанция может быть идентифицирована как имя инстанции + идентификатор инстанции.
} PERF_INSTANCE_HEADER,
*PPERF_INSTANCE_HEADER;



typedef struct _PERF_COUNTER_IDENTIFIER {//Струкутра для идентификации СП
 GUID CounterSetGuid;		//GUID 
 unsigned long Status;		//Win32 код ошибки показывающий успешна ли операция
 unsigned long Size;		//размер структуры и имени инстанции в байтах
 unsigned long CounterId;	//числовой идентификатор СП
 unsigned long InstanceId;	//идентификатор инстанции
 unsigned long Index;		//позиция, возвращаемая методом PerfLibV2QueryCounterData
 unsigned long Reserved;	//д.б. =0
} PERF_COUNTER_IDENTIFIER,	//
*PPERF_COUNTER_IDENTIFIER;	//	



typedef struct _PERF_DATA_HEADER {//Используется в начале последовательности блоков заголовков СП
 unsigned long dwTotalSize;			//размер данных
 unsigned long dwNumCounter;		//кол-во возвращаемых СП
 unsigned __int64 PerfTimeStamp;	//часы высокого разрешения
 unsigned __int64 PerfTime100NSec;	//кол-во 100 нс интервалов от 01.01.1601 UTC
 unsigned __int64 PerfFreq;			//Частота часов выского разрешения
 SYSTEMTIME SystemTime;				//Время собирания данных со стороны провайдера
} PERF_DATA_HEADER,					//
*PPERF_DATA_HEADER;					//



typedef struct _PERF_COUNTER_HEADER {//структура используется в начале блока заголовка СП
 unsigned long dwStatus;//Win32 код ошибки показывающий успешна ли операция
 unsigned long dwType;	//Тип СП: PERF_ERROR_RETURN, PERF_SINGLE_COUNTER - запрос вернул значение СП одной инстанции, PERF_MULTI_COUNTERS - запрос вернул мн-во значений СП, PERF_MULTI_INSTANCES - запрос вернул значения с неск. инстанций СП, PERF_COUNTERSET - запрос вернул значения всех иснтанций всех СП в CounterSet
 unsigned long dwSize;	//размер структуры
 unsigned long Reserved;// =0
} PERF_COUNTER_HEADER,	//
*PPERFCOUNTERHEADER;	//



typedef struct _PERF_COUNTER_DATA {//Структура, используемая к блоке заголовка СП
 unsigned long dwDataSize;	//размер данных СП
 unsigned long dwSize;		//размер структуры + данных СП
} PERF_COUNTER_DATA,
*PPERF_COUNTER_DATA;




typedef struct _PERF_MULTI_INSTANCES {//используется в блоке заголовка СП
 unsigned long dwTotalSize;//размер заголовка и данных
 unsigned long dwInstances;//кол-во инстанций с которых собираются данные
} PERF_MULTI_INSTANCES,
*PPERF_MULTI_INSTANCES;


typedef struct _PERF_MULTI_COUNTERS {//Используется в блоке заголовка СП
 unsigned long dwSize;		//Размер структуры и идентификаторов СП
 unsigned long dwCounters;	//кол-во СП
} PERF_MULTI_COUNTERS,
*PPERF_MULTI_COUNTERS;

Со стороны клиента ПЗСП сквозная. Вызовы из высокого уровня передаются напрямую к транспортному. Обратно также.

