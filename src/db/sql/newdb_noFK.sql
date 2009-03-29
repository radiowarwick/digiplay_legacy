--

-- PostgreSQL database dump
--

-- Started on 2009-03-15 18:54:59 GMT

SET client_encoding = 'UTF8';
SET standard_conforming_strings = off;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET escape_string_warning = off;

SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 1887 (class 1259 OID 20289)
-- Dependencies: 6
-- Name: advertschedule; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE advertschedule (
    advert_schedule_id serial NOT NULL,
    audio_id integer NOT NULL,
    start_date integer NOT NULL,
    end_date integer NOT NULL,
    time_start integer,
    time_end integer,
    frequency smallint NOT NULL,
    last_modified int NOT NULL,
    PRIMARY KEY (advert_schedule_id)
);


ALTER TABLE public.advertschedule OWNER TO postgres;

--
-- TOC entry 1888 (class 1259 OID 20292)
-- Dependencies: 6
-- Name: album; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE album (
    album_id serial NOT NULL,
    name character varying NOT NULL,
    last_modified integer NOT NULL,
    PRIMARY KEY (album_id)
);


ALTER TABLE public.album OWNER TO postgres;

CREATE TABLE audioalbum (
    audio_id integer NOT NULL,
    album_id integer NOT NULL,
    PRIMARY KEY (audio_id, album_id)
);

ALTER TABLE public.audioalbum OWNER TO postgres;

CREATE TABLE albumkeyword (
    album_id integer NOT NULL,
    keyword_id integer NOT NULL,
    PRIMARY KEY (album_id, keyword_id)
);

ALTER TABLE public.albumkeyword OWNER TO postgres;

CREATE TABLE audioproperty (
    audio_id integer NOT NULL,
    property_id integer NOT NULL,
    val character varying,
    last_modified integer NOT NULL,
    PRIMARY KEY (audio_id, property_id)
);

ALTER TABLE public.audioproperty OWNER TO postgres;

CREATE TABLE property (
    property_id serial NOT NULL,
    property_group_id integer NOT NULL,
    name character varying NOT NULL,
    description character varying,
    last_modified integer NOT NULL,
    PRIMARY KEY (property_id)
);

ALTER TABLE public.property OWNER TO postgres;

CREATE TABLE propertygroup (
    property_group_id serial NOT NULL,
    name character varying NOT NULL,
    description character varying,
    last_modified integer NOT NULL,
    PRIMARY KEY (property_group_id)
);

ALTER TABLE public.propertygroup OWNER TO postgres;

--
-- TOC entry 1889 (class 1259 OID 20298)
-- Dependencies: 6
-- Name: audio_archive; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audioarchive (
    audio_archive_id serial NOT NULL,
    audio_id integer NOT NULL,
    priority integer NOT NULL,
    name character varying NOT NULL,
    localpath character varying NOT NULL,
    remotepath character varying NOT NULL,
    last_modified integer NOT NULL,
    PRIMARY KEY (audio_archive_id)
);


ALTER TABLE public.audioarchive OWNER TO postgres;

--
-- TOC entry 1890 (class 1259 OID 20304)
-- Dependencies: 6
-- Name: artist; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE artist (
    artist_id serial NOT NULL,
    name character varying NOT NULL,
    last_modified integer NOT NULL,
    PRIMARY KEY (artist_id)
);


ALTER TABLE public.artist OWNER TO postgres;

--
-- TOC entry 1891 (class 1259 OID 20310)
-- Dependencies: 6
-- Name: artistkeyword; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE artistkeyword (
    artist_id integer NOT NULL,
    keyword_id integer NOT NULL,
    PRIMARY KEY (artist_id, keyword_id)
);


ALTER TABLE public.artistkeyword OWNER TO postgres;

--
-- TOC entry 1892 (class 1259 OID 20313)
-- Dependencies: 2450 2451 2452 6
-- Name: audio; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audio (
    audio_id serial NOT NULL,
    file_id integer NOT NULL,
    md5 character(32) NOT NULL,
    length_smpl integer NOT NULL,
    start_smpl integer NOT NULL,
    end_smpl integer NOT NULL,
    intro_smpl integer NOT NULL,
    extro_smpl integer NOT NULL,
    audio_type_id integer NOT NULL,
    creator_id integer NOT NULL,
    import_date integer NOT NULL,
    title character varying NOT NULL,
    sustainer boolean,
    flagged boolean,
    censor boolean,
    filetype character varying NOT NULL,
    last_modified integer NOT NULL,
    PRIMARY KEY (audio_id)
);


ALTER TABLE public.audio OWNER TO postgres;

--
-- TOC entry 1893 (class 1259 OID 20322)
-- Dependencies: 6
-- Name: audioartist; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audioartist (
    audio_id integer NOT NULL,
    artist_id integer NOT NULL,
    PRIMARY KEY (audio_id, artist_id)
);


ALTER TABLE public.audioartist OWNER TO postgres;

--
-- TOC entry 1894 (class 1259 OID 20325)
-- Dependencies: 6
-- Name: audiocomment; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audiocomment (
    audio_comment_id serial NOT NULL,
    audio_id integer NOT NULL,
    user_id integer NOT NULL,
    creation_date integer NOT NULL,
    comment character varying,
    last_modified integer NOT NULL,
    PRIMARY KEY (audio_comment_id)
);


ALTER TABLE public.audiocomment OWNER TO postgres;

--
-- TOC entry 1896 (class 1259 OID 20336)
-- Dependencies: 6
-- Name: audioext; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audioext (
    audio_ext_id serial NOT NULL,
    library_id character varying NOT NULL,
    title character varying NOT NULL,
    artist_name character varying NOT NULL,
    album_name character varying,
    last_modified integer NOT NULL,
    PRIMARY KEY (audio_ext_id)
);


ALTER TABLE public.audioext OWNER TO postgres;

--
-- TOC entry 1898 (class 1259 OID 20345)
-- Dependencies: 6
-- Name: audiojinglepkg; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audiojinglepkg (
    audio_id integer NOT NULL,
    jingle_pkg_id integer NOT NULL,
    PRIMARY KEY (audio_id, jingle_pkg_id)
);


ALTER TABLE public.audiojinglepkg OWNER TO postgres;

--
-- TOC entry 1899 (class 1259 OID 20348)
-- Dependencies: 6
-- Name: audiokeyword; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audiokeyword (
    audio_id integer NOT NULL,
    keyword_id integer NOT NULL,
    PRIMARY KEY (audio_id, keyword_id)
);


ALTER TABLE public.audiokeyword OWNER TO postgres;

--
-- TOC entry 1900 (class 1259 OID 20351)
-- Dependencies: 6
-- Name: audiolog; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audiolog (
    audio_log_id serial NOT NULL,
    audio_id integer NOT NULL,
    user_id integer NOT NULL,
    download_date integer NOT NULL,
    last_modified integer NOT NULL,
    PRIMARY KEY (audio_log_id)
);


ALTER TABLE public.audiolog OWNER TO postgres;

--
-- TOC entry 1901 (class 1259 OID 20354)
-- Dependencies: 6
-- Name: audioplaylist; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audioplaylist (
    audio_id integer NOT NULL,
    playlist_id integer NOT NULL,
    PRIMARY KEY (audio_id, playlist_id)
);


ALTER TABLE public.audioplaylist OWNER TO postgres;

--
-- TOC entry 1902 (class 1259 OID 20357)
-- Dependencies: 6
-- Name: audiotype; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audiotype (
    audio_type_id serial NOT NULL,
    name character varying NOT NULL,
    description character varying,
    last_modified integer NOT NULL,
    PRIMARY KEY (audio_type_id)
);


ALTER TABLE public.audiotype OWNER TO postgres;

--
-- TOC entry 1913 (class 1259 OID 20413)
-- Dependencies: 6
-- Name: bin; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE bin (
    bin_id serial NOT NULL,
    name character varying NOT NULL,
    description character varying,
    last_modified integer NOT NULL,
    PRIMARY KEY (bin_id)
);


ALTER TABLE public.bin OWNER TO postgres;

--
-- TOC entry 1914 (class 1259 OID 20419)
-- Dependencies: 6
-- Name: binartist; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE binartist (
    artist_id integer NOT NULL,
    bin_id integer NOT NULL,
    PRIMARY KEY (artist_id, bin_id)
);


ALTER TABLE public.binartist OWNER TO postgres;

--
-- TOC entry 1915 (class 1259 OID 20422)
-- Dependencies: 6
-- Name: binaudio; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE binaudio (
    audio_id integer NOT NULL,
    bin_id integer NOT NULL,
    PRIMARY KEY (audio_id, bin_id)
);


ALTER TABLE public.binaudio OWNER TO postgres;

--
-- TOC entry 1916 (class 1259 OID 20425)
-- Dependencies: 6
-- Name: binkeyword; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE binkeyword (
    keyword_id integer NOT NULL,
    bin_id integer NOT NULL,
    PRIMARY KEY (keyword_id, bin_id)
);


ALTER TABLE public.binkeyword OWNER TO postgres;

--
-- TOC entry 1917 (class 1259 OID 20428)
-- Dependencies: 6
-- Name: binschedule; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE binschedule (
    bin_schedule_id serial NOT NULL,
    bin_id integer NOT NULL,
    bin_type_id integer NOT NULL,
    day_start integer NOT NULL,
    hour_start integer NOT NULL,
    length_hours integer NOT NULL,
    bin_start integer NOT NULL,
    bin_end integer NOT NULL,
    description character varying,
    last_modified integer NOT NULL,
    PRIMARY KEY (bin_schedule_id)
);


ALTER TABLE public.binschedule OWNER TO postgres;

--
-- TOC entry 1918 (class 1259 OID 20434)
-- Dependencies: 6
-- Name: cartproperty; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cartproperty (
    cart_property_id serial NOT NULL,
    name character varying NOT NULL,
    description character varying,
    last_modified integer NOT NULL,
    PRIMARY KEY (cart_property_id)
);


ALTER TABLE public.cartproperty OWNER TO postgres;

--
-- TOC entry 1919 (class 1259 OID 20440)
-- Dependencies: 6
-- Name: cartaudio; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cartaudio (
    cart_audio_id serial NOT NULL,
    audio_id integer NOT NULL,
    cartstyle_id integer NOT NULL,
    cart_id integer NOT NULL,
    cartwall_id integer NOT NULL,
    text character varying NOT NULL,
    last_modified integer NOT NULL,
    PRIMARY KEY (cart_audio_id)
);


ALTER TABLE public.cartaudio OWNER TO postgres;

--
-- TOC entry 1920 (class 1259 OID 20446)
-- Dependencies: 6
-- Name: cartsets; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cartset (
    cartset_id serial NOT NULL,
    file_id integer NOT NULL,
    name character varying NOT NULL,
    description character varying,
    last_modified integer NOT NULL,
    PRIMARY KEY (cartset_id)
);

ALTER TABLE public.cartset OWNER TO postgres;

--
-- TOC entry 1924 (class 1259 OID 20463)
-- Dependencies: 6
-- Name: cartstyleprop; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cartstyleprop (
    cart_style_prop_id serial NOT NULL,
    cart_style_id integer NOT NULL,
    cart_property_id integer NOT NULL,
    value character varying NOT NULL,
    last_modified integer NOT NULL,
    PRIMARY KEY (cart_style_prop_id)
);


ALTER TABLE public.cartstyleprop OWNER TO postgres;

--
-- TOC entry 1925 (class 1259 OID 20469)
-- Dependencies: 6
-- Name: cartstyle; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cartstyle (
    cart_style_id serial NOT NULL,
    name character varying NOT NULL,
    description character varying,
    last_modified integer NOT NULL,
    PRIMARY KEY (cart_style_id)
);


ALTER TABLE public.cartstyle OWNER TO postgres;

--
-- TOC entry 1926 (class 1259 OID 20475)
-- Dependencies: 6
-- Name: cartwalls; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cartwall (
    cartwall_id serial NOT NULL,
    name character varying NOT NULL,
    cartset_id integer NOT NULL,
    page integer NOT NULL,
    description character varying,
    last_modified integer NOT NULL,
    PRIMARY KEY (cartwall_id)
);


ALTER TABLE public.cartwall OWNER TO postgres;

--
-- TOC entry 1931 (class 1259 OID 20508)
-- Dependencies: 6
-- Name: config; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE config (
    config_id serial NOT NULL,
    name character varying,
    description character varying,
    last_modified integer NOT NULL,
    PRIMARY KEY (config_id)
);


ALTER TABLE public.config OWNER TO postgres;

--
-- TOC entry 1932 (class 1259 OID 20514)
-- Dependencies: 6
-- Name: configuration; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE configuration (
    configuration_id serial NOT NULL,
    parameter character varying NOT NULL,
    val character varying NOT NULL,
    location integer NOT NULL,
    last_modified integer NOT NULL,
    PRIMARY KEY (configuration_id)
);


ALTER TABLE public.configuration OWNER TO postgres;

--
-- TOC entry 1933 (class 1259 OID 20520)
-- Dependencies: 2507 6
-- Name: file; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE file (
    file_id serial NOT NULL,
    parent integer NOT NULL,
    name character varying NOT NULL,
    owner_id integer NOT NULL,
    group_id integer NOT NULL,
    entity_id integer,
    entity_type integer,
    user_r boolean NOT NULL,
    user_w boolean NOT NULL,
    user_x boolean NOT NULL,
    group_r boolean NOT NULL,
    group_w boolean NOT NULL,
    group_x boolean NOT NULL,
    all_r boolean NOT NULL,
    all_w boolean NOT NULL,
    all_x boolean NOT NULL,
    created integer NOT NULL,
    last_modified integer NOT NULL,
    PRIMARY KEY (file_id)
);


ALTER TABLE public.file OWNER TO postgres;

--
-- TOC entry 1936 (class 1259 OID 20533)
-- Dependencies: 6
-- Name: email; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE email (
    email_id serial NOT NULL,
    new_flag boolean NOT NULL,
    recieved integer NOT NULL,
    sender character varying NOT NULL,
    subject character varying,
    body character varying,
    last_modified integer NOT NULL,
    PRIMARY KEY (email_id)
);


ALTER TABLE public.email OWNER TO postgres;

--
-- TOC entry 1937 (class 1259 OID 20539)
-- Dependencies: 6
-- Name: extfeed; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE extfeed (
    ext_feed_id serial NOT NULL,
    name character varying NOT NULL,
    device character varying NOT NULL,
    last_modified integer NOT NULL,
    PRIMARY KEY (ext_feed_id)
);


ALTER TABLE public.extfeed OWNER TO postgres;

--
-- TOC entry 1941 (class 1259 OID 20567)
-- Dependencies: 6
-- Name: group; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE "group" (
    group_id serial NOT NULL,
    name character varying,
    description character varying,
    last_modified integer NOT NULL,
    PRIMARY KEY (group_id)
);


ALTER TABLE public."group" OWNER TO postgres;

--
-- TOC entry 1942 (class 1259 OID 20573)
-- Dependencies: 6
-- Name: jinglepkg; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE jinglepkg (
    jingle_pkg_id serial NOT NULL,
    name character varying NOT NULL,
    description character varying,
    enabled boolean NOT NULL,
    last_modified integer NOT NULL,
    PRIMARY KEY (jingle_pkg_id)
);


ALTER TABLE public.jinglepkg OWNER TO postgres;

--
-- TOC entry 1944 (class 1259 OID 20585)
-- Dependencies: 6
-- Name: keyword; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE keyword (
    keyword_id serial NOT NULL,
    name character varying NOT NULL,
    hash character varying,
    last_modified integer NOT NULL,
    PRIMARY KEY (keyword_id)
);


ALTER TABLE public.keyword OWNER TO postgres;

--
-- TOC entry 1949 (class 1259 OID 20617)
-- Dependencies: 6
-- Name: playlist; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE playlist (
    playlist_id serial NOT NULL,
    name character varying NOT NULL,
    last_modified integer NOT NULL,
    PRIMARY KEY (playlist_id)
);


ALTER TABLE public.playlist OWNER TO postgres;

CREATE TABLE privilage (
    privilage_id serial NOT NULL,
    name character varying NOT NULL,
    description character varying,
    last_modified integer NOT NULL,
    PRIMARY KEY (privilage_id)
);


ALTER TABLE public.privilage OWNER TO postgres;

CREATE TABLE userprivilage (
    user_id integer NOT NULL,
    privilage_id integer NOT NULL,
    PRIMARY KEY (user_id, privilage_id)
);

ALTER TABLE public.userprivilage OWNER TO postgres;

CREATE TABLE groupprivilage (
    group_id integer NOT NULL,
    privilage_id integer NOT NULL,
    PRIMARY KEY (group_id, privilage_id)
);

ALTER TABLE public.groupprivilage OWNER TO postgres;

--
-- TOC entry 1953 (class 1259 OID 20633)
-- Dependencies: 6
-- Name: request; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE request (
    request_id serial NOT NULL,
    name character varying,
    artist_name character varying,
    request_date integer NOT NULL,
    user_id integer NOT NULL,
    last_modified integer NOT NULL,
    PRIMARY KEY (request_id)
);


ALTER TABLE public.request OWNER TO postgres;

--
-- TOC entry 1954 (class 1259 OID 20639)
-- Dependencies: 6
-- Name: scripts; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE script (
    script_id serial NOT NULL,
    name character varying NOT NULL,
    contents character varying,
    length integer,
    file_id integer NOT NULL,
    creation_date integer NOT NULL,
    last_modified integer NOT NULL,
    PRIMARY KEY (script_id)
);


ALTER TABLE public.script OWNER TO postgres;

--
-- TOC entry 1960 (class 1259 OID 20671)
-- Dependencies: 6
-- Name: showitem; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE showitem (
    show_item_id serial NOT NULL,
    show_plan_id integer NOT NULL,
    location smallint NOT NULL,
    title character varying NOT NULL,
    audio_id integer,
    script_id integer,
    comment character varying,
    length integer NOT NULL,
    last_modified integer NOT NULL,
    PRIMARY KEY (show_item_id)
);


ALTER TABLE public.showitem OWNER TO postgres;

--
-- TOC entry 1963 (class 1259 OID 20685)
-- Dependencies: 6
-- Name: showplan; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE showplan (
    show_plan_id serial NOT NULL,
    file_id integer NOT NULL,
    name character varying NOT NULL,
    show_date integer,
    completed boolean NOT NULL,
    description character varying,
    last_modified integer NOT NULL,
    PRIMARY KEY (show_plan_id)
);


ALTER TABLE public.showplan OWNER TO postgres;

--
-- TOC entry 1968 (class 1259 OID 20705)
-- Dependencies: 6
-- Name: sustschedule; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE sustschedule (
    sust_schedule_id serial NOT NULL,
    audio_id integer,
    ext_feed_id integer,
    ext_feed_length integer,
    start integer NOT NULL,
    trim_start_smpl integer NOT NULL,
    trim_end_smpl integer NOT NULL,
    fade_in integer NOT NULL,
    fade_out integer NOT NULL,
    last_modified integer NOT NULL,
    PRIMARY KEY (sust_schedule_id)
);


ALTER TABLE public.sustschedule OWNER TO postgres;

--
-- TOC entry 1977 (class 1259 OID 20745)
-- Dependencies: 2580 2581 6
-- Name: user; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE "user" (
    user_id serial NOT NULL,
    username character varying,
    password character(32),
    enabled boolean NOT NULL,
    ghost boolean NOT NULL,
    last_modified integer NOT NULL,
    PRIMARY KEY (user_id)
);


ALTER TABLE public.user OWNER TO postgres;

--
-- TOC entry 1978 (class 1259 OID 20753)
-- Dependencies: 6
-- Name: userconfig; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE userconfig (
    user_config_id serial NOT NULL,
    user_id integer NOT NULL,
    config_id integer NOT NULL,
    val character varying,
    last_modified integer NOT NULL,
    PRIMARY KEY (user_config_id)
);


ALTER TABLE public.userconfig OWNER TO postgres;

--
-- TOC entry 1979 (class 1259 OID 20759)
-- Dependencies: 6
-- Name: usergroup; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE usergroup (
    user_id integer NOT NULL,
    group_id integer NOT NULL,
    PRIMARY KEY (user_id, group_id)
);

