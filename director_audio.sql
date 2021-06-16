--
-- PostgreSQL database dump
--

-- Dumped from database version 13.2
-- Dumped by pg_dump version 13.2

-- Started on 2021-06-16 22:35:06

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 201 (class 1259 OID 16417)
-- Name: Директор; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Директор" (
    "Директор" character varying(30),
    "Название фирмы" character varying(40),
    "Адрес" character varying(30),
    "Телефон" character varying(11),
    "ИНН" character varying(25),
    "Дата начала действия" date,
    "Дата окончания действия" date,
    id integer NOT NULL
);


ALTER TABLE public."Директор" OWNER TO postgres;

--
-- TOC entry 211 (class 1259 OID 16666)
-- Name: Директор_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Директор_id_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Директор_id_seq" OWNER TO postgres;

--
-- TOC entry 3110 (class 0 OID 0)
-- Dependencies: 211
-- Name: Директор_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Директор_id_seq" OWNED BY public."Директор".id;


--
-- TOC entry 202 (class 1259 OID 16444)
-- Name: Договор_с_клиентом; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Договор_с_клиентом" (
    "Дата_заключения" date,
    "Дата_окончания" date,
    "Директор" integer,
    id integer NOT NULL,
    "Договор_с_клиентом" character varying(45)
);


ALTER TABLE public."Договор_с_клиентом" OWNER TO postgres;

--
-- TOC entry 212 (class 1259 OID 16680)
-- Name: Договор с клиентом_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Договор с клиентом_id_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Договор с клиентом_id_seq" OWNER TO postgres;

--
-- TOC entry 3111 (class 0 OID 0)
-- Dependencies: 212
-- Name: Договор с клиентом_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Договор с клиентом_id_seq" OWNED BY public."Договор_с_клиентом".id;


--
-- TOC entry 203 (class 1259 OID 16449)
-- Name: Договор_с_поставщиком; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Договор_с_поставщиком" (
    "Дата_заключения" date,
    "Дата_окончания" date,
    id integer NOT NULL,
    "Директор" integer,
    "Договор_с_поставщиком" character varying(45)
);


ALTER TABLE public."Договор_с_поставщиком" OWNER TO postgres;

--
-- TOC entry 213 (class 1259 OID 16688)
-- Name: Договор с поставщиком_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Договор с поставщиком_id_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Договор с поставщиком_id_seq" OWNER TO postgres;

--
-- TOC entry 3112 (class 0 OID 0)
-- Dependencies: 213
-- Name: Договор с поставщиком_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Договор с поставщиком_id_seq" OWNED BY public."Договор_с_поставщиком".id;


--
-- TOC entry 206 (class 1259 OID 16533)
-- Name: Заказ_на_поставку; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Заказ_на_поставку" (
    "Дата_заказа" date,
    "Дата_поставки" date,
    "Отметка_об_оплате" boolean,
    id integer NOT NULL,
    "Договор_с_поставщиком" integer,
    "Отметка_о_доставке" boolean,
    "Заказ_на_поставку" character varying
);


ALTER TABLE public."Заказ_на_поставку" OWNER TO postgres;

--
-- TOC entry 214 (class 1259 OID 16701)
-- Name: Заказ на поставку_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Заказ на поставку_id_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Заказ на поставку_id_seq" OWNER TO postgres;

--
-- TOC entry 3113 (class 0 OID 0)
-- Dependencies: 214
-- Name: Заказ на поставку_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Заказ на поставку_id_seq" OWNED BY public."Заказ_на_поставку".id;


--
-- TOC entry 207 (class 1259 OID 16559)
-- Name: Заказ_на_продажу; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Заказ_на_продажу" (
    "Дата_заказа" date,
    "Дата_поставки" date,
    "Отметка_об_оплате" boolean,
    "Отметка_о_доставке" boolean,
    id integer NOT NULL,
    "Договор_с_клиентом" integer,
    "Заказ_на_продажу" character varying(45)
);


ALTER TABLE public."Заказ_на_продажу" OWNER TO postgres;

--
-- TOC entry 215 (class 1259 OID 16715)
-- Name: Заказ на продажу_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Заказ на продажу_id_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Заказ на продажу_id_seq" OWNER TO postgres;

--
-- TOC entry 3114 (class 0 OID 0)
-- Dependencies: 215
-- Name: Заказ на продажу_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Заказ на продажу_id_seq" OWNED BY public."Заказ_на_продажу".id;


--
-- TOC entry 210 (class 1259 OID 16650)
-- Name: Каталог_товар; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Каталог_товар" (
    "Наименование_товара" character varying(30),
    "Цена" money,
    "Характеристика" text,
    "Категория" character varying(30),
    "Бренд" character varying(10),
    "Поставщик" integer,
    id integer NOT NULL
);


ALTER TABLE public."Каталог_товар" OWNER TO postgres;

--
-- TOC entry 204 (class 1259 OID 16464)
-- Name: Клиент; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Клиент" (
    "Адрес" character varying(50),
    "Телефон" character varying(11),
    "ИНН" character varying(25),
    id integer NOT NULL,
    "Директор" integer
);


ALTER TABLE public."Клиент" OWNER TO postgres;

--
-- TOC entry 216 (class 1259 OID 16733)
-- Name: Клиент_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Клиент_id_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Клиент_id_seq" OWNER TO postgres;

--
-- TOC entry 3115 (class 0 OID 0)
-- Dependencies: 216
-- Name: Клиент_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Клиент_id_seq" OWNED BY public."Клиент".id;


--
-- TOC entry 200 (class 1259 OID 16411)
-- Name: Поставщик; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Поставщик" (
    "Название фирмы" character varying(30),
    "Адрес" character varying(50),
    "Телефон" character varying(10),
    "ИНН" character varying(25),
    id integer NOT NULL,
    "Директор" integer,
    "Поставщик" character varying(45)
);


ALTER TABLE public."Поставщик" OWNER TO postgres;

--
-- TOC entry 220 (class 1259 OID 16785)
-- Name: Поставщик_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Поставщик_id_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Поставщик_id_seq" OWNER TO postgres;

--
-- TOC entry 3116 (class 0 OID 0)
-- Dependencies: 220
-- Name: Поставщик_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Поставщик_id_seq" OWNED BY public."Поставщик".id;


--
-- TOC entry 205 (class 1259 OID 16474)
-- Name: Склад; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Склад" (
    "Количество" integer,
    id integer NOT NULL,
    "Склад" character varying(45)
);


ALTER TABLE public."Склад" OWNER TO postgres;

--
-- TOC entry 219 (class 1259 OID 16765)
-- Name: Склад_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Склад_id_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Склад_id_seq" OWNER TO postgres;

--
-- TOC entry 3117 (class 0 OID 0)
-- Dependencies: 219
-- Name: Склад_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Склад_id_seq" OWNED BY public."Склад".id;


--
-- TOC entry 208 (class 1259 OID 16606)
-- Name: Товар_в_заказе_клиента; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Товар_в_заказе_клиента" (
    "Количество" integer,
    "Цена" money,
    "Промежуточный_итог" money,
    id integer NOT NULL,
    "Заказ_на_продажу" integer
);


ALTER TABLE public."Товар_в_заказе_клиента" OWNER TO postgres;

--
-- TOC entry 218 (class 1259 OID 16757)
-- Name: Товар_в_заказе_клиента_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Товар_в_заказе_клиента_id_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Товар_в_заказе_клиента_id_seq" OWNER TO postgres;

--
-- TOC entry 3118 (class 0 OID 0)
-- Dependencies: 218
-- Name: Товар_в_заказе_клиента_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Товар_в_заказе_клиента_id_seq" OWNED BY public."Товар_в_заказе_клиента".id;


--
-- TOC entry 209 (class 1259 OID 16626)
-- Name: Товар_в_заказе_поставщика; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Товар_в_заказе_поставщика" (
    "Количество" integer,
    "Цена" money,
    "Промежуточный_итог" money,
    id integer NOT NULL,
    "Заказ_на_поставку" integer
);


ALTER TABLE public."Товар_в_заказе_поставщика" OWNER TO postgres;

--
-- TOC entry 217 (class 1259 OID 16749)
-- Name: Товар_в_заказе_поставщика_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Товар_в_заказе_поставщика_id_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Товар_в_заказе_поставщика_id_seq" OWNER TO postgres;

--
-- TOC entry 3119 (class 0 OID 0)
-- Dependencies: 217
-- Name: Товар_в_заказе_поставщика_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Товар_в_заказе_поставщика_id_seq" OWNED BY public."Товар_в_заказе_поставщика".id;


--
-- TOC entry 2913 (class 2604 OID 16668)
-- Name: Директор id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Директор" ALTER COLUMN id SET DEFAULT nextval('public."Директор_id_seq"'::regclass);


--
-- TOC entry 2914 (class 2604 OID 16682)
-- Name: Договор_с_клиентом id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Договор_с_клиентом" ALTER COLUMN id SET DEFAULT nextval('public."Договор с клиентом_id_seq"'::regclass);


--
-- TOC entry 2915 (class 2604 OID 16690)
-- Name: Договор_с_поставщиком id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Договор_с_поставщиком" ALTER COLUMN id SET DEFAULT nextval('public."Договор с поставщиком_id_seq"'::regclass);


--
-- TOC entry 2918 (class 2604 OID 16703)
-- Name: Заказ_на_поставку id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Заказ_на_поставку" ALTER COLUMN id SET DEFAULT nextval('public."Заказ на поставку_id_seq"'::regclass);


--
-- TOC entry 2919 (class 2604 OID 16717)
-- Name: Заказ_на_продажу id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Заказ_на_продажу" ALTER COLUMN id SET DEFAULT nextval('public."Заказ на продажу_id_seq"'::regclass);


--
-- TOC entry 2916 (class 2604 OID 16735)
-- Name: Клиент id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Клиент" ALTER COLUMN id SET DEFAULT nextval('public."Клиент_id_seq"'::regclass);


--
-- TOC entry 2912 (class 2604 OID 16787)
-- Name: Поставщик id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Поставщик" ALTER COLUMN id SET DEFAULT nextval('public."Поставщик_id_seq"'::regclass);


--
-- TOC entry 2917 (class 2604 OID 16767)
-- Name: Склад id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Склад" ALTER COLUMN id SET DEFAULT nextval('public."Склад_id_seq"'::regclass);


--
-- TOC entry 2920 (class 2604 OID 16759)
-- Name: Товар_в_заказе_клиента id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Товар_в_заказе_клиента" ALTER COLUMN id SET DEFAULT nextval('public."Товар_в_заказе_клиента_id_seq"'::regclass);


--
-- TOC entry 2921 (class 2604 OID 16751)
-- Name: Товар_в_заказе_поставщика id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Товар_в_заказе_поставщика" ALTER COLUMN id SET DEFAULT nextval('public."Товар_в_заказе_поставщика_id_seq"'::regclass);


--
-- TOC entry 3085 (class 0 OID 16417)
-- Dependencies: 201
-- Data for Name: Директор; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Директор" ("Директор", "Название фирмы", "Адрес", "Телефон", "ИНН", "Дата начала действия", "Дата окончания действия", id) FROM stdin;
Иван	OOO Стройгаз\n	Обводный канал 161\n	8800234123	312312321004124213	2013-12-18	2024-12-18	2
12321321	ыыыы	sadasd		123456789765432134567	2000-01-01	2000-01-01	4
Игорь	Битсы	ул.Ленина 17	+792122231	12312516787654322345	2000-01-01	2021-01-01	12
Илья	Маршалл	ул Пушкина. дом колотушкина	989131123	82171402140174011241	2017-01-07	2023-01-01	13
Егор ДокторДре	ДокторДре	Владимерская	812312321	2131232141212421	2019-01-23	2024-03-04	14
\.


--
-- TOC entry 3086 (class 0 OID 16444)
-- Dependencies: 202
-- Data for Name: Договор_с_клиентом; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Договор_с_клиентом" ("Дата_заключения", "Дата_окончания", "Директор", id, "Договор_с_клиентом") FROM stdin;
2021-01-01	2021-01-02	2	19	Договор о покупке супер гитары
\.


--
-- TOC entry 3087 (class 0 OID 16449)
-- Dependencies: 203
-- Data for Name: Договор_с_поставщиком; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Договор_с_поставщиком" ("Дата_заключения", "Дата_окончания", id, "Директор", "Договор_с_поставщиком") FROM stdin;
2000-01-01	2000-01-01	19	2	ПОставка наушников
2018-01-01	2021-01-01	20	14	Поставка наушников от доктор дре
2019-07-01	2022-01-01	21	2	Поставка мониторов
2000-01-01	2027-01-01	22	12	Комбики
\.


--
-- TOC entry 3090 (class 0 OID 16533)
-- Dependencies: 206
-- Data for Name: Заказ_на_поставку; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Заказ_на_поставку" ("Дата_заказа", "Дата_поставки", "Отметка_об_оплате", id, "Договор_с_поставщиком", "Отметка_о_доставке", "Заказ_на_поставку") FROM stdin;
2021-07-03	2021-07-03	t	1	19	t	наушники ббитс 777
\.


--
-- TOC entry 3091 (class 0 OID 16559)
-- Dependencies: 207
-- Data for Name: Заказ_на_продажу; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Заказ_на_продажу" ("Дата_заказа", "Дата_поставки", "Отметка_об_оплате", "Отметка_о_доставке", id, "Договор_с_клиентом", "Заказ_на_продажу") FROM stdin;
2021-06-01	2021-07-07	t	f	16	19	Продажа супер гитары Honor
\.


--
-- TOC entry 3094 (class 0 OID 16650)
-- Dependencies: 210
-- Data for Name: Каталог_товар; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Каталог_товар" ("Наименование_товара", "Цена", "Характеристика", "Категория", "Бренд", "Поставщик", id) FROM stdin;
Fender Stratocaster	3 000,00 ?	Два хамбакера	Муз.инструменты	Fender	7	2
\.


--
-- TOC entry 3088 (class 0 OID 16464)
-- Dependencies: 204
-- Data for Name: Клиент; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Клиент" ("Адрес", "Телефон", "ИНН", id, "Директор") FROM stdin;
фв	фыв	112	6	2
ул. Сусово	+883218323	12312525125125151	8	\N
\.


--
-- TOC entry 3084 (class 0 OID 16411)
-- Dependencies: 200
-- Data for Name: Поставщик; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Поставщик" ("Название фирмы", "Адрес", "Телефон", "ИНН", id, "Директор", "Поставщик") FROM stdin;
АудиоБомба	г.Кострома	8953111111	31215126214124	1	\N	Иван
АудиоБомба	г.Кострома	8953111111	31215126214124	2	\N	Иван
				3	\N	as
				4	\N	
				5	\N	
				6	\N	
Аудиотех	Украина	+773232312	3121251244142142	7	2	Женя
Радио Комбик	г. Санкт-Петербург	883123128	321003131203120312	8	12	Иван Иванов
\.


--
-- TOC entry 3089 (class 0 OID 16474)
-- Dependencies: 205
-- Data for Name: Склад; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Склад" ("Количество", id, "Склад") FROM stdin;
3	1	Наушники
3	2	Гитары
3	3	Мониторы
\.


--
-- TOC entry 3092 (class 0 OID 16606)
-- Dependencies: 208
-- Data for Name: Товар_в_заказе_клиента; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Товар_в_заказе_клиента" ("Количество", "Цена", "Промежуточный_итог", id, "Заказ_на_продажу") FROM stdin;
1	300,00 ?	200,00 ?	1	16
\.


--
-- TOC entry 3093 (class 0 OID 16626)
-- Dependencies: 209
-- Data for Name: Товар_в_заказе_поставщика; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Товар_в_заказе_поставщика" ("Количество", "Цена", "Промежуточный_итог", id, "Заказ_на_поставку") FROM stdin;
2	4 000,00 ?	300,00 ?	1	1
\.


--
-- TOC entry 3120 (class 0 OID 0)
-- Dependencies: 211
-- Name: Директор_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Директор_id_seq"', 14, true);


--
-- TOC entry 3121 (class 0 OID 0)
-- Dependencies: 212
-- Name: Договор с клиентом_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Договор с клиентом_id_seq"', 19, true);


--
-- TOC entry 3122 (class 0 OID 0)
-- Dependencies: 213
-- Name: Договор с поставщиком_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Договор с поставщиком_id_seq"', 22, true);


--
-- TOC entry 3123 (class 0 OID 0)
-- Dependencies: 214
-- Name: Заказ на поставку_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Заказ на поставку_id_seq"', 1, true);


--
-- TOC entry 3124 (class 0 OID 0)
-- Dependencies: 215
-- Name: Заказ на продажу_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Заказ на продажу_id_seq"', 16, true);


--
-- TOC entry 3125 (class 0 OID 0)
-- Dependencies: 216
-- Name: Клиент_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Клиент_id_seq"', 8, true);


--
-- TOC entry 3126 (class 0 OID 0)
-- Dependencies: 220
-- Name: Поставщик_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Поставщик_id_seq"', 8, true);


--
-- TOC entry 3127 (class 0 OID 0)
-- Dependencies: 219
-- Name: Склад_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Склад_id_seq"', 3, true);


--
-- TOC entry 3128 (class 0 OID 0)
-- Dependencies: 218
-- Name: Товар_в_заказе_клиента_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Товар_в_заказе_клиента_id_seq"', 1, true);


--
-- TOC entry 3129 (class 0 OID 0)
-- Dependencies: 217
-- Name: Товар_в_заказе_поставщика_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Товар_в_заказе_поставщика_id_seq"', 1, true);


--
-- TOC entry 2925 (class 2606 OID 16674)
-- Name: Директор Директор_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Директор"
    ADD CONSTRAINT "Директор_pkey" PRIMARY KEY (id);


--
-- TOC entry 2927 (class 2606 OID 16687)
-- Name: Договор_с_клиентом Договор с клиентом_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Договор_с_клиентом"
    ADD CONSTRAINT "Договор с клиентом_pkey" PRIMARY KEY (id);


--
-- TOC entry 2929 (class 2606 OID 16695)
-- Name: Договор_с_поставщиком Договор_с_поставщиком_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Договор_с_поставщиком"
    ADD CONSTRAINT "Договор_с_поставщиком_pkey" PRIMARY KEY (id);


--
-- TOC entry 2937 (class 2606 OID 16722)
-- Name: Заказ_на_продажу Заказ на продажу_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Заказ_на_продажу"
    ADD CONSTRAINT "Заказ на продажу_pkey" PRIMARY KEY (id);


--
-- TOC entry 2935 (class 2606 OID 16709)
-- Name: Заказ_на_поставку Заказ_на_поставку_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Заказ_на_поставку"
    ADD CONSTRAINT "Заказ_на_поставку_pkey" PRIMARY KEY (id);


--
-- TOC entry 2943 (class 2606 OID 16869)
-- Name: Каталог_товар Каталог_товар_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Каталог_товар"
    ADD CONSTRAINT "Каталог_товар_pkey" PRIMARY KEY (id);


--
-- TOC entry 2931 (class 2606 OID 16740)
-- Name: Клиент Клиент_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Клиент"
    ADD CONSTRAINT "Клиент_pkey" PRIMARY KEY (id);


--
-- TOC entry 2923 (class 2606 OID 16792)
-- Name: Поставщик Поставщик_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Поставщик"
    ADD CONSTRAINT "Поставщик_pkey" PRIMARY KEY (id);


--
-- TOC entry 2933 (class 2606 OID 16772)
-- Name: Склад Склад_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Склад"
    ADD CONSTRAINT "Склад_pkey" PRIMARY KEY (id);


--
-- TOC entry 2939 (class 2606 OID 16764)
-- Name: Товар_в_заказе_клиента Товар_в_заказе_клиента_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Товар_в_заказе_клиента"
    ADD CONSTRAINT "Товар_в_заказе_клиента_pkey" PRIMARY KEY (id);


--
-- TOC entry 2941 (class 2606 OID 16756)
-- Name: Товар_в_заказе_поставщика Товар_в_заказе_поставщика_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Товар_в_заказе_поставщика"
    ADD CONSTRAINT "Товар_в_заказе_поставщика_pkey" PRIMARY KEY (id);


--
-- TOC entry 2946 (class 2606 OID 16696)
-- Name: Договор_с_поставщиком Директор; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Договор_с_поставщиком"
    ADD CONSTRAINT "Директор" FOREIGN KEY ("Директор") REFERENCES public."Директор"(id) NOT VALID;


--
-- TOC entry 2945 (class 2606 OID 16728)
-- Name: Договор_с_клиентом Директор; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Договор_с_клиентом"
    ADD CONSTRAINT "Директор" FOREIGN KEY ("Директор") REFERENCES public."Директор"(id) NOT VALID;


--
-- TOC entry 2947 (class 2606 OID 16741)
-- Name: Клиент Директор; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Клиент"
    ADD CONSTRAINT "Директор" FOREIGN KEY ("Директор") REFERENCES public."Директор"(id) NOT VALID;


--
-- TOC entry 2944 (class 2606 OID 16813)
-- Name: Поставщик Директор; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Поставщик"
    ADD CONSTRAINT "Директор" FOREIGN KEY ("Директор") REFERENCES public."Директор"(id) NOT VALID;


--
-- TOC entry 2949 (class 2606 OID 16861)
-- Name: Заказ_на_продажу Договор_с_клиентом; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Заказ_на_продажу"
    ADD CONSTRAINT "Договор_с_клиентом" FOREIGN KEY ("Договор_с_клиентом") REFERENCES public."Договор_с_клиентом"(id) NOT VALID;


--
-- TOC entry 2948 (class 2606 OID 16818)
-- Name: Заказ_на_поставку Договор_с_поставщиком; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Заказ_на_поставку"
    ADD CONSTRAINT "Договор_с_поставщиком" FOREIGN KEY ("Договор_с_поставщиком") REFERENCES public."Договор_с_поставщиком"(id) NOT VALID;


--
-- TOC entry 2951 (class 2606 OID 16803)
-- Name: Товар_в_заказе_поставщика Заказ_на_поставку; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Товар_в_заказе_поставщика"
    ADD CONSTRAINT "Заказ_на_поставку" FOREIGN KEY ("Заказ_на_поставку") REFERENCES public."Заказ_на_поставку"(id) NOT VALID;


--
-- TOC entry 2950 (class 2606 OID 16798)
-- Name: Товар_в_заказе_клиента Заказ_на_продажу; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Товар_в_заказе_клиента"
    ADD CONSTRAINT "Заказ_на_продажу" FOREIGN KEY ("Заказ_на_продажу") REFERENCES public."Заказ_на_продажу"(id) NOT VALID;


--
-- TOC entry 2952 (class 2606 OID 16793)
-- Name: Каталог_товар Поставщик; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Каталог_товар"
    ADD CONSTRAINT "Поставщик" FOREIGN KEY ("Поставщик") REFERENCES public."Поставщик"(id) NOT VALID;


--
-- TOC entry 2953 (class 2606 OID 16870)
-- Name: Каталог_товар склад; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Каталог_товар"
    ADD CONSTRAINT "склад" FOREIGN KEY (id) REFERENCES public."Склад"(id) NOT VALID;


-- Completed on 2021-06-16 22:35:07

--
-- PostgreSQL database dump complete
--

