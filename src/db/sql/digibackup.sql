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
    id integer NOT NULL,
    audioid integer NOT NULL,
    start_date date NOT NULL,
    end_date date NOT NULL,
    time_start time without time zone,
    time_end time without time zone,
    frequency smallint NOT NULL
);


ALTER TABLE public.advertschedule OWNER TO postgres;

--
-- TOC entry 1888 (class 1259 OID 20292)
-- Dependencies: 6
-- Name: albums; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE albums (
    id integer NOT NULL,
    name character varying NOT NULL,
    alt_name character varying
);


ALTER TABLE public.albums OWNER TO postgres;

--
-- TOC entry 1889 (class 1259 OID 20298)
-- Dependencies: 6
-- Name: archives; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE archives (
    id integer NOT NULL,
    name character varying NOT NULL,
    localpath character varying NOT NULL,
    remotepath character varying NOT NULL
);


ALTER TABLE public.archives OWNER TO postgres;

--
-- TOC entry 1890 (class 1259 OID 20304)
-- Dependencies: 6
-- Name: artists; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE artists (
    id integer NOT NULL,
    name character varying NOT NULL,
    alt_name character varying
);


ALTER TABLE public.artists OWNER TO postgres;

--
-- TOC entry 1891 (class 1259 OID 20310)
-- Dependencies: 6
-- Name: artistskeywords; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE artistskeywords (
    id integer NOT NULL,
    artistid integer NOT NULL,
    keywordid integer NOT NULL
);


ALTER TABLE public.artistskeywords OWNER TO postgres;

--
-- TOC entry 1892 (class 1259 OID 20313)
-- Dependencies: 2450 2451 2452 6
-- Name: audio; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audio (
    id integer NOT NULL,
    md5 character(32) NOT NULL,
    archive integer NOT NULL,
    length_smpl integer NOT NULL,
    start_smpl integer NOT NULL,
    end_smpl integer NOT NULL,
    intro_smpl integer NOT NULL,
    extro_smpl integer NOT NULL,
    type integer NOT NULL,
    creator integer NOT NULL,
    creation_date integer NOT NULL,
    import_date integer NOT NULL,
    title character varying NOT NULL,
    music_album integer DEFAULT 1 NOT NULL,
    music_track smallint,
    music_released smallint,
    advert_company integer,
    advert_description character varying,
    origin character varying,
    reclibid character varying,
    sustainer character(1),
    flagged character(1),
    censor character(1),
    notes character varying,
    param_vol smallint,
    param_speed smallint,
    param_mood smallint,
    param_endstyle smallint,
    lifespan integer DEFAULT 1 NOT NULL,
    rip_result character varying,
    filetype character varying DEFAULT 'raw'::character varying NOT NULL
);


ALTER TABLE public.audio OWNER TO postgres;

--
-- TOC entry 1893 (class 1259 OID 20322)
-- Dependencies: 6
-- Name: audioartists; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audioartists (
    id integer NOT NULL,
    audioid integer NOT NULL,
    artistid integer NOT NULL
);


ALTER TABLE public.audioartists OWNER TO postgres;

--
-- TOC entry 1894 (class 1259 OID 20325)
-- Dependencies: 6
-- Name: audiocomments; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audiocomments (
    id integer NOT NULL,
    audioid integer NOT NULL,
    userid integer NOT NULL,
    creationdate integer NOT NULL,
    comment character varying
);


ALTER TABLE public.audiocomments OWNER TO postgres;

--
-- TOC entry 1895 (class 1259 OID 20331)
-- Dependencies: 2456 2457 6
-- Name: audiodir; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audiodir (
    id integer NOT NULL,
    audioid integer NOT NULL,
    dirid integer NOT NULL,
    linktype smallint DEFAULT 0 NOT NULL,
    inherit character(1) DEFAULT 't'::bpchar NOT NULL
);


ALTER TABLE public.audiodir OWNER TO postgres;

--
-- TOC entry 1896 (class 1259 OID 20336)
-- Dependencies: 6
-- Name: audioext; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audioext (
    id integer NOT NULL,
    library_id character varying NOT NULL,
    title character varying NOT NULL,
    artist_name character varying NOT NULL,
    album_name character varying
);


ALTER TABLE public.audioext OWNER TO postgres;

--
-- TOC entry 1897 (class 1259 OID 20342)
-- Dependencies: 6
-- Name: audiogroups; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audiogroups (
    id integer NOT NULL,
    audioid integer NOT NULL,
    groupid integer NOT NULL,
    permissions bit(8) NOT NULL
);


ALTER TABLE public.audiogroups OWNER TO postgres;

--
-- TOC entry 1898 (class 1259 OID 20345)
-- Dependencies: 6
-- Name: audiojinglepkgs; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audiojinglepkgs (
    id integer NOT NULL,
    audioid integer NOT NULL,
    jinglepkgid integer NOT NULL,
    jingletypeid integer NOT NULL
);


ALTER TABLE public.audiojinglepkgs OWNER TO postgres;

--
-- TOC entry 1899 (class 1259 OID 20348)
-- Dependencies: 6
-- Name: audiokeywords; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audiokeywords (
    id integer NOT NULL,
    audioid integer NOT NULL,
    keywordid integer NOT NULL
);


ALTER TABLE public.audiokeywords OWNER TO postgres;

--
-- TOC entry 1900 (class 1259 OID 20351)
-- Dependencies: 6
-- Name: audiolog; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audiolog (
    id integer NOT NULL,
    audioid integer NOT NULL,
    userid integer NOT NULL,
    downloaddate date NOT NULL
);


ALTER TABLE public.audiolog OWNER TO postgres;

--
-- TOC entry 1901 (class 1259 OID 20354)
-- Dependencies: 6
-- Name: audioplaylists; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audioplaylists (
    id integer NOT NULL,
    audioid integer NOT NULL,
    playlistid integer NOT NULL
);


ALTER TABLE public.audioplaylists OWNER TO postgres;

--
-- TOC entry 1902 (class 1259 OID 20357)
-- Dependencies: 6
-- Name: audiotypes; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audiotypes (
    id integer NOT NULL,
    name character varying NOT NULL,
    description character varying
);


ALTER TABLE public.audiotypes OWNER TO postgres;

--
-- TOC entry 1903 (class 1259 OID 20363)
-- Dependencies: 6
-- Name: audiousers; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE audiousers (
    id integer NOT NULL,
    audioid integer NOT NULL,
    userid integer NOT NULL,
    permissions bit(8) NOT NULL
);


ALTER TABLE public.audiousers OWNER TO postgres;

--
-- TOC entry 1904 (class 1259 OID 20366)
-- Dependencies: 6
-- Name: aw_items; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE aw_items (
    id integer NOT NULL,
    audio_id integer NOT NULL,
    style_id integer NOT NULL,
    item integer NOT NULL,
    wall_id integer NOT NULL,
    text character varying NOT NULL
);


ALTER TABLE public.aw_items OWNER TO postgres;

--
-- TOC entry 1905 (class 1259 OID 20372)
-- Dependencies: 6
-- Name: aw_props; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE aw_props (
    id integer NOT NULL,
    name character varying NOT NULL,
    note character varying
);


ALTER TABLE public.aw_props OWNER TO postgres;

--
-- TOC entry 1906 (class 1259 OID 20378)
-- Dependencies: 6
-- Name: aw_sets; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE aw_sets (
    id integer NOT NULL,
    name character varying NOT NULL,
    description character varying
);


ALTER TABLE public.aw_sets OWNER TO postgres;

--
-- TOC entry 1907 (class 1259 OID 20384)
-- Dependencies: 2470 2471 6
-- Name: aw_sets_dir; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE aw_sets_dir (
    id integer NOT NULL,
    set_id integer NOT NULL,
    dir_id integer NOT NULL,
    linktype smallint DEFAULT 0 NOT NULL,
    inherit character(1) DEFAULT 't'::bpchar NOT NULL
);


ALTER TABLE public.aw_sets_dir OWNER TO postgres;

--
-- TOC entry 1908 (class 1259 OID 20389)
-- Dependencies: 6
-- Name: aw_sets_groups; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE aw_sets_groups (
    id integer NOT NULL,
    set_id integer NOT NULL,
    group_id integer NOT NULL,
    permissions bit(8) NOT NULL
);


ALTER TABLE public.aw_sets_groups OWNER TO postgres;

--
-- TOC entry 1909 (class 1259 OID 20392)
-- Dependencies: 6
-- Name: aw_sets_users; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE aw_sets_users (
    id integer NOT NULL,
    set_id integer NOT NULL,
    user_id integer NOT NULL,
    permissions bit(8) NOT NULL
);


ALTER TABLE public.aw_sets_users OWNER TO postgres;

--
-- TOC entry 1910 (class 1259 OID 20395)
-- Dependencies: 6
-- Name: aw_styles; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE aw_styles (
    id integer NOT NULL,
    name character varying NOT NULL,
    description character varying
);


ALTER TABLE public.aw_styles OWNER TO postgres;

--
-- TOC entry 1911 (class 1259 OID 20401)
-- Dependencies: 6
-- Name: aw_styles_props; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE aw_styles_props (
    id integer NOT NULL,
    style_id integer NOT NULL,
    prop_id integer NOT NULL,
    value character varying NOT NULL
);


ALTER TABLE public.aw_styles_props OWNER TO postgres;

--
-- TOC entry 1912 (class 1259 OID 20407)
-- Dependencies: 6
-- Name: aw_walls; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE aw_walls (
    id integer NOT NULL,
    name character varying NOT NULL,
    set_id integer NOT NULL,
    page integer NOT NULL,
    description character varying
);


ALTER TABLE public.aw_walls OWNER TO postgres;

--
-- TOC entry 1913 (class 1259 OID 20413)
-- Dependencies: 6
-- Name: bins; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE bins (
    id integer NOT NULL,
    name character varying NOT NULL,
    description character varying
);


ALTER TABLE public.bins OWNER TO postgres;

--
-- TOC entry 1914 (class 1259 OID 20419)
-- Dependencies: 6
-- Name: binsartists; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE binsartists (
    id integer NOT NULL,
    artistid integer NOT NULL,
    binid integer NOT NULL
);


ALTER TABLE public.binsartists OWNER TO postgres;

--
-- TOC entry 1915 (class 1259 OID 20422)
-- Dependencies: 6
-- Name: binsaudio; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE binsaudio (
    id integer NOT NULL,
    audioid integer NOT NULL,
    binid integer NOT NULL
);


ALTER TABLE public.binsaudio OWNER TO postgres;

--
-- TOC entry 1916 (class 1259 OID 20425)
-- Dependencies: 6
-- Name: binskeywords; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE binskeywords (
    id integer NOT NULL,
    keywordid integer NOT NULL,
    binid integer NOT NULL
);


ALTER TABLE public.binskeywords OWNER TO postgres;

--
-- TOC entry 1917 (class 1259 OID 20428)
-- Dependencies: 6
-- Name: binsschedule; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE binsschedule (
    id integer NOT NULL,
    binid integer NOT NULL,
    bintype integer NOT NULL,
    day_start integer NOT NULL,
    hour_start integer NOT NULL,
    length_hours integer NOT NULL,
    binstart integer NOT NULL,
    binend integer NOT NULL,
    notes character varying
);


ALTER TABLE public.binsschedule OWNER TO postgres;

--
-- TOC entry 1918 (class 1259 OID 20434)
-- Dependencies: 6
-- Name: cartproperties; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cartproperties (
    id integer NOT NULL,
    name character varying NOT NULL,
    note character varying
);


ALTER TABLE public.cartproperties OWNER TO postgres;

--
-- TOC entry 1919 (class 1259 OID 20440)
-- Dependencies: 6
-- Name: cartsaudio; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cartsaudio (
    id integer NOT NULL,
    audioid integer NOT NULL,
    cartstyleid integer NOT NULL,
    cart integer NOT NULL,
    cartwallid integer NOT NULL,
    text character varying NOT NULL
);


ALTER TABLE public.cartsaudio OWNER TO postgres;

--
-- TOC entry 1920 (class 1259 OID 20446)
-- Dependencies: 6
-- Name: cartsets; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cartsets (
    id integer NOT NULL,
    name character varying NOT NULL,
    description character varying
);


ALTER TABLE public.cartsets OWNER TO postgres;

--
-- TOC entry 1921 (class 1259 OID 20452)
-- Dependencies: 2486 2487 6
-- Name: cartsetsdir; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cartsetsdir (
    id integer NOT NULL,
    cartsetid integer NOT NULL,
    dirid integer NOT NULL,
    linktype smallint DEFAULT 0 NOT NULL,
    inherit character(1) DEFAULT 't'::bpchar NOT NULL
);


ALTER TABLE public.cartsetsdir OWNER TO postgres;

--
-- TOC entry 1922 (class 1259 OID 20457)
-- Dependencies: 6
-- Name: cartsetsgroups; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cartsetsgroups (
    id integer NOT NULL,
    cartsetid integer NOT NULL,
    groupid integer NOT NULL,
    permissions bit(8) NOT NULL
);


ALTER TABLE public.cartsetsgroups OWNER TO postgres;

--
-- TOC entry 1923 (class 1259 OID 20460)
-- Dependencies: 6
-- Name: cartsetsusers; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cartsetsusers (
    id integer NOT NULL,
    cartsetid integer NOT NULL,
    userid integer NOT NULL,
    permissions bit(8) NOT NULL
);


ALTER TABLE public.cartsetsusers OWNER TO postgres;

--
-- TOC entry 1924 (class 1259 OID 20463)
-- Dependencies: 6
-- Name: cartstyleprops; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cartstyleprops (
    id integer NOT NULL,
    cartstyleid integer NOT NULL,
    cartpropertyid integer NOT NULL,
    value character varying NOT NULL
);


ALTER TABLE public.cartstyleprops OWNER TO postgres;

--
-- TOC entry 1925 (class 1259 OID 20469)
-- Dependencies: 6
-- Name: cartstyles; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cartstyles (
    id integer NOT NULL,
    name character varying NOT NULL,
    description character varying
);


ALTER TABLE public.cartstyles OWNER TO postgres;

--
-- TOC entry 1926 (class 1259 OID 20475)
-- Dependencies: 6
-- Name: cartwalls; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cartwalls (
    id integer NOT NULL,
    name character varying NOT NULL,
    cartsetid integer NOT NULL,
    page integer NOT NULL,
    description character varying
);


ALTER TABLE public.cartwalls OWNER TO postgres;

--
-- TOC entry 1927 (class 1259 OID 20481)
-- Dependencies: 6
-- Name: changelog; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE changelog (
    id integer NOT NULL,
    datetime integer NOT NULL,
    userid integer NOT NULL,
    relation character varying NOT NULL,
    record integer NOT NULL,
    field character varying NOT NULL,
    oldvalue character varying NOT NULL,
    comment character varying
);


ALTER TABLE public.changelog OWNER TO postgres;

--
-- TOC entry 1928 (class 1259 OID 20487)
-- Dependencies: 2495 2496 2497 6
-- Name: cmscontent; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cmscontent (
    contentid integer NOT NULL,
    regionid integer DEFAULT 0 NOT NULL,
    "timestamp" integer DEFAULT 0 NOT NULL,
    content bytea NOT NULL,
    userid integer DEFAULT 0 NOT NULL
);


ALTER TABLE public.cmscontent OWNER TO postgres;

--
-- TOC entry 1929 (class 1259 OID 20496)
-- Dependencies: 2499 2500 2501 6
-- Name: cmsregions; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE cmsregions (
    regionid integer NOT NULL,
    name character varying(32) DEFAULT ''::character varying NOT NULL,
    editrealm integer NOT NULL,
    viewrealm integer NOT NULL,
    inlinetoolbar character varying(16) DEFAULT 'Basic'::character varying NOT NULL,
    windowtoolbar character varying(16) DEFAULT 'Default'::character varying NOT NULL
);


ALTER TABLE public.cmsregions OWNER TO postgres;

--
-- TOC entry 1930 (class 1259 OID 20502)
-- Dependencies: 6
-- Name: companies; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE companies (
    id integer NOT NULL,
    name character varying NOT NULL
);


ALTER TABLE public.companies OWNER TO postgres;

--
-- TOC entry 1931 (class 1259 OID 20508)
-- Dependencies: 6
-- Name: configs; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE configs (
    id integer NOT NULL,
    name character varying,
    description character varying
);


ALTER TABLE public.configs OWNER TO postgres;

--
-- TOC entry 1932 (class 1259 OID 20514)
-- Dependencies: 6
-- Name: configuration; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE configuration (
    id integer NOT NULL,
    parameter character varying NOT NULL,
    val character varying NOT NULL,
    location integer NOT NULL
);


ALTER TABLE public.configuration OWNER TO postgres;

--
-- TOC entry 1933 (class 1259 OID 20520)
-- Dependencies: 2507 6
-- Name: dir; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE dir (
    id integer NOT NULL,
    parent integer,
    name character varying,
    notes character varying,
    inherit character(1) DEFAULT 't'::bpchar NOT NULL
);


ALTER TABLE public.dir OWNER TO postgres;

--
-- TOC entry 1934 (class 1259 OID 20527)
-- Dependencies: 6
-- Name: dirgroups; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE dirgroups (
    id integer NOT NULL,
    dirid integer,
    groupid integer,
    permissions bit(8)
);


ALTER TABLE public.dirgroups OWNER TO postgres;

--
-- TOC entry 1935 (class 1259 OID 20530)
-- Dependencies: 6
-- Name: dirusers; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE dirusers (
    id integer NOT NULL,
    dirid integer,
    userid integer,
    permissions bit(8)
);


ALTER TABLE public.dirusers OWNER TO postgres;

--
-- TOC entry 1936 (class 1259 OID 20533)
-- Dependencies: 6
-- Name: email; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE email (
    id integer NOT NULL,
    new_flag character(1) NOT NULL,
    datetime integer NOT NULL,
    sender character varying NOT NULL,
    subject character varying,
    body character varying
);


ALTER TABLE public.email OWNER TO postgres;

--
-- TOC entry 1937 (class 1259 OID 20539)
-- Dependencies: 6
-- Name: extfeeds; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE extfeeds (
    id integer NOT NULL,
    name character varying NOT NULL,
    device character varying NOT NULL
);


ALTER TABLE public.extfeeds OWNER TO postgres;

--
-- TOC entry 1938 (class 1259 OID 20545)
-- Dependencies: 2513 2514 6
-- Name: fieldvalidators; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE fieldvalidators (
    ruleid integer NOT NULL,
    vrclassname character varying(45) DEFAULT ''::character varying NOT NULL,
    description text NOT NULL,
    modulename character varying(16) DEFAULT ''::character varying NOT NULL
);


ALTER TABLE public.fieldvalidators OWNER TO postgres;

--
-- TOC entry 1939 (class 1259 OID 20553)
-- Dependencies: 2515 2516 2517 2518 6
-- Name: formfields; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE formfields (
    fieldid integer NOT NULL,
    formname character varying(32) DEFAULT ''::character varying NOT NULL,
    fieldname character varying(32) DEFAULT ''::character varying NOT NULL,
    ruleid integer DEFAULT 0 NOT NULL,
    modulename character varying(16) DEFAULT ''::character varying NOT NULL
);


ALTER TABLE public.formfields OWNER TO postgres;

--
-- TOC entry 1940 (class 1259 OID 20560)
-- Dependencies: 2520 2521 2522 2523 6
-- Name: forms; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE forms (
    formid integer NOT NULL,
    formname character varying(32) DEFAULT ''::character varying NOT NULL,
    modelclass character varying(32) DEFAULT ''::character varying NOT NULL,
    modulename character varying(32) DEFAULT ''::character varying NOT NULL,
    realmid integer DEFAULT 0 NOT NULL,
    validatorname character varying(32),
    validatormodule character varying(32)
);


ALTER TABLE public.forms OWNER TO postgres;

--
-- TOC entry 1941 (class 1259 OID 20567)
-- Dependencies: 6
-- Name: groups; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE groups (
    id integer NOT NULL,
    name character varying,
    description character varying
);


ALTER TABLE public.groups OWNER TO postgres;

--
-- TOC entry 1942 (class 1259 OID 20573)
-- Dependencies: 6
-- Name: jinglepkgs; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE jinglepkgs (
    id integer NOT NULL,
    name character varying NOT NULL,
    description character varying NOT NULL,
    enabled character(1) NOT NULL
);


ALTER TABLE public.jinglepkgs OWNER TO postgres;

--
-- TOC entry 1943 (class 1259 OID 20579)
-- Dependencies: 6
-- Name: jingletypes; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE jingletypes (
    id integer NOT NULL,
    name character varying NOT NULL,
    description character varying
);


ALTER TABLE public.jingletypes OWNER TO postgres;

--
-- TOC entry 1944 (class 1259 OID 20585)
-- Dependencies: 6
-- Name: keywords; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE keywords (
    id integer NOT NULL,
    name character varying NOT NULL,
    name_similar character varying
);


ALTER TABLE public.keywords OWNER TO postgres;

--
-- TOC entry 1945 (class 1259 OID 20591)
-- Dependencies: 6
-- Name: lifespans; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE lifespans (
    id integer NOT NULL,
    name character varying NOT NULL,
    data integer NOT NULL,
    description character varying
);


ALTER TABLE public.lifespans OWNER TO postgres;

--
-- TOC entry 1946 (class 1259 OID 20597)
-- Dependencies: 6
-- Name: log; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE log (
    id integer NOT NULL,
    location integer NOT NULL,
    userid integer NOT NULL,
    datetime integer NOT NULL,
    track_title character varying NOT NULL,
    track_artist character varying NOT NULL
);


ALTER TABLE public.log OWNER TO postgres;

--
-- TOC entry 1947 (class 1259 OID 20603)
-- Dependencies: 2532 2533 6
-- Name: logentries; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE logentries (
    entryid integer NOT NULL,
    message text NOT NULL,
    level character varying(16) DEFAULT ''::character varying NOT NULL,
    module character varying(16),
    notes text,
    notify_date timestamp(6) without time zone DEFAULT now() NOT NULL
);


ALTER TABLE public.logentries OWNER TO postgres;

--
-- TOC entry 2115 (class 1259 OID 22348)
-- Dependencies: 6
-- Name: news; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE news (
    id integer NOT NULL,
    creator integer NOT NULL,
    created integer NOT NULL,
    title character varying(255) NOT NULL,
    body text NOT NULL
);


ALTER TABLE public.news OWNER TO postgres;

--
-- TOC entry 1948 (class 1259 OID 20611)
-- Dependencies: 6
-- Name: patches; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE patches (
    id integer NOT NULL,
    branch character varying,
    version integer
);


ALTER TABLE public.patches OWNER TO postgres;

--
-- TOC entry 1949 (class 1259 OID 20617)
-- Dependencies: 6
-- Name: playlists; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE playlists (
    id integer NOT NULL,
    name character varying NOT NULL
);


ALTER TABLE public.playlists OWNER TO postgres;

--
-- TOC entry 1950 (class 1259 OID 20623)
-- Dependencies: 6
-- Name: realmgrouplink; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE realmgrouplink (
    groupid integer NOT NULL,
    realmid integer NOT NULL,
    allow character(1)
);


ALTER TABLE public.realmgrouplink OWNER TO postgres;

--
-- TOC entry 1951 (class 1259 OID 20626)
-- Dependencies: 2537 6
-- Name: realms; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE realms (
    realmid integer NOT NULL,
    name character varying(32) DEFAULT ''::character varying NOT NULL,
    parentid integer NOT NULL,
    description character varying(128),
    depth smallint,
    realmpath character varying(255)
);


ALTER TABLE public.realms OWNER TO postgres;

--
-- TOC entry 1952 (class 1259 OID 20630)
-- Dependencies: 6
-- Name: realmuserlink; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE realmuserlink (
    userid integer NOT NULL,
    realmid integer NOT NULL,
    allow character(1)
);


ALTER TABLE public.realmuserlink OWNER TO postgres;

--
-- TOC entry 1953 (class 1259 OID 20633)
-- Dependencies: 6
-- Name: requests; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE requests (
    id integer NOT NULL,
    name character varying,
    artistname character varying,
    date integer NOT NULL,
    userid integer NOT NULL
);


ALTER TABLE public.requests OWNER TO postgres;

--
-- TOC entry 1954 (class 1259 OID 20639)
-- Dependencies: 6
-- Name: scripts; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE scripts (
    id integer NOT NULL,
    name character varying NOT NULL,
    contents character varying,
    length integer,
    userid integer NOT NULL,
    creationdate integer NOT NULL
);


ALTER TABLE public.scripts OWNER TO postgres;

--
-- TOC entry 1955 (class 1259 OID 20645)
-- Dependencies: 2542 2543 6
-- Name: scriptsdir; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE scriptsdir (
    id integer NOT NULL,
    scriptid integer NOT NULL,
    dirid integer NOT NULL,
    linktype smallint DEFAULT 0 NOT NULL,
    inherit character(1) DEFAULT 't'::bpchar NOT NULL
);


ALTER TABLE public.scriptsdir OWNER TO postgres;

--
-- TOC entry 1956 (class 1259 OID 20650)
-- Dependencies: 6
-- Name: scriptsgroups; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE scriptsgroups (
    id integer NOT NULL,
    scriptid integer NOT NULL,
    groupid integer NOT NULL,
    permissions bit(8) NOT NULL
);


ALTER TABLE public.scriptsgroups OWNER TO postgres;

--
-- TOC entry 1957 (class 1259 OID 20653)
-- Dependencies: 6
-- Name: scriptsusers; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE scriptsusers (
    id integer NOT NULL,
    scriptid integer NOT NULL,
    userid integer NOT NULL,
    permissions bit(8) NOT NULL
);


ALTER TABLE public.scriptsusers OWNER TO postgres;

--
-- TOC entry 1958 (class 1259 OID 20656)
-- Dependencies: 2546 2547 2548 2549 6
-- Name: sessions; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE sessions (
    sessionid integer NOT NULL,
    useragent character varying(128) DEFAULT ''::character varying NOT NULL,
    ip character varying(15) DEFAULT ''::character varying NOT NULL,
    rndidentifier character varying(14) DEFAULT ''::character varying NOT NULL,
    lastaccess character varying(12) DEFAULT ''::character varying NOT NULL
);


ALTER TABLE public.sessions OWNER TO postgres;

--
-- TOC entry 1959 (class 1259 OID 20663)
-- Dependencies: 2552 2553 6
-- Name: sessionvalues; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE sessionvalues (
    valueid integer NOT NULL,
    sessionid integer DEFAULT 0 NOT NULL,
    skey character varying(32) DEFAULT ''::character varying NOT NULL,
    svalue bytea NOT NULL
);


ALTER TABLE public.sessionvalues OWNER TO postgres;

--
-- TOC entry 1960 (class 1259 OID 20671)
-- Dependencies: 6
-- Name: showitems; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE showitems (
    id integer NOT NULL,
    showplanid integer NOT NULL,
    "position" smallint NOT NULL,
    title character varying NOT NULL,
    audioid integer,
    scriptid integer,
    comment character varying,
    length integer NOT NULL
);


ALTER TABLE public.showitems OWNER TO postgres;

--
-- TOC entry 1961 (class 1259 OID 20677)
-- Dependencies: 2556 2557 6
-- Name: showplandir; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE showplandir (
    id integer NOT NULL,
    showplanid integer NOT NULL,
    dirid integer NOT NULL,
    linktype smallint DEFAULT 0 NOT NULL,
    inherit character(1) DEFAULT 't'::bpchar NOT NULL
);


ALTER TABLE public.showplandir OWNER TO postgres;

--
-- TOC entry 1962 (class 1259 OID 20682)
-- Dependencies: 6
-- Name: showplangroups; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE showplangroups (
    id integer NOT NULL,
    showplanid integer NOT NULL,
    groupid integer NOT NULL,
    permissions bit(8) NOT NULL
);


ALTER TABLE public.showplangroups OWNER TO postgres;

--
-- TOC entry 1963 (class 1259 OID 20685)
-- Dependencies: 6
-- Name: showplans; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE showplans (
    id integer NOT NULL,
    name character varying NOT NULL,
    userid integer NOT NULL,
    creationdate integer NOT NULL,
    showdate integer,
    completed boolean NOT NULL
);


ALTER TABLE public.showplans OWNER TO postgres;

--
-- TOC entry 1964 (class 1259 OID 20691)
-- Dependencies: 2561 2562 6
-- Name: showplansdir; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE showplansdir (
    id integer NOT NULL,
    showplanid integer NOT NULL,
    dirid integer NOT NULL,
    linktype smallint DEFAULT 0 NOT NULL,
    inherit character(1) DEFAULT 't'::bpchar NOT NULL
);


ALTER TABLE public.showplansdir OWNER TO postgres;

--
-- TOC entry 1965 (class 1259 OID 20696)
-- Dependencies: 6
-- Name: showplansgroups; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE showplansgroups (
    id integer NOT NULL,
    showplanid integer NOT NULL,
    groupid integer NOT NULL,
    permissions bit(8) NOT NULL
);


ALTER TABLE public.showplansgroups OWNER TO postgres;

--
-- TOC entry 1966 (class 1259 OID 20699)
-- Dependencies: 6
-- Name: showplansusers; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE showplansusers (
    id integer NOT NULL,
    showplanid integer NOT NULL,
    userid integer NOT NULL,
    permissions bit(8) NOT NULL
);


ALTER TABLE public.showplansusers OWNER TO postgres;

--
-- TOC entry 1967 (class 1259 OID 20702)
-- Dependencies: 6
-- Name: showplanusers; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE showplanusers (
    id integer NOT NULL,
    showplanid integer NOT NULL,
    userid integer NOT NULL,
    permissions bit(8) NOT NULL
);


ALTER TABLE public.showplanusers OWNER TO postgres;

--
-- TOC entry 1968 (class 1259 OID 20705)
-- Dependencies: 6
-- Name: sustschedule; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE sustschedule (
    id integer NOT NULL,
    audioid integer,
    extfeedid integer,
    extfeed_length integer,
    start integer NOT NULL,
    trim_start_smpl integer NOT NULL,
    trim_end_smpl integer NOT NULL,
    fade_in integer NOT NULL,
    fade_out integer NOT NULL
);


ALTER TABLE public.sustschedule OWNER TO postgres;

--
-- TOC entry 1969 (class 1259 OID 20708)
-- Dependencies: 6
-- Name: tasks; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE tasks (
    id integer NOT NULL,
    name character varying NOT NULL,
    description character varying NOT NULL,
    sql_query character varying,
    process character varying,
    parameters character varying
);


ALTER TABLE public.tasks OWNER TO postgres;

--
-- TOC entry 1970 (class 1259 OID 20714)
-- Dependencies: 6
-- Name: taskschedule; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE taskschedule (
    id integer NOT NULL,
    taskid integer NOT NULL,
    dayofweek smallint NOT NULL,
    timeofday integer NOT NULL
);


ALTER TABLE public.taskschedule OWNER TO postgres;

--
-- TOC entry 1971 (class 1259 OID 20717)
-- Dependencies: 2569 2570 2571 2572 6
-- Name: templates; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE templates (
    templateid integer NOT NULL,
    filename character varying(32) DEFAULT ''::character varying NOT NULL,
    viewerclassname character varying(32) DEFAULT ''::character varying NOT NULL,
    realmid integer DEFAULT 0 NOT NULL,
    modulename character varying(16) DEFAULT ''::character varying NOT NULL
);


ALTER TABLE public.templates OWNER TO postgres;

--
-- TOC entry 1972 (class 1259 OID 20724)
-- Dependencies: 6
-- Name: txcategories; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE txcategories (
    id integer NOT NULL,
    name character varying,
    description character varying,
    bgcolour character(6) NOT NULL
);


ALTER TABLE public.txcategories OWNER TO postgres;

--
-- TOC entry 1973 (class 1259 OID 20730)
-- Dependencies: 6
-- Name: txschedule; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE txschedule (
    id integer NOT NULL,
    txshowid integer NOT NULL,
    starttime integer NOT NULL,
    endtime integer NOT NULL
);


ALTER TABLE public.txschedule OWNER TO postgres;

--
-- TOC entry 1974 (class 1259 OID 20733)
-- Dependencies: 6
-- Name: txshows; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE txshows (
    id integer NOT NULL,
    name character varying NOT NULL,
    description character varying,
    picture character varying,
    blurb character varying,
    txcategoryid integer NOT NULL
);


ALTER TABLE public.txshows OWNER TO postgres;

--
-- TOC entry 1975 (class 1259 OID 20739)
-- Dependencies: 6
-- Name: txshowskeywords; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE txshowskeywords (
    id integer NOT NULL,
    txshowid integer,
    keywordid integer
);


ALTER TABLE public.txshowskeywords OWNER TO postgres;

--
-- TOC entry 1976 (class 1259 OID 20742)
-- Dependencies: 6
-- Name: txshowsusers; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE txshowsusers (
    id integer NOT NULL,
    txshowid integer,
    userid integer
);


ALTER TABLE public.txshowsusers OWNER TO postgres;

--
-- TOC entry 1977 (class 1259 OID 20745)
-- Dependencies: 2580 2581 6
-- Name: users; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE users (
    id integer NOT NULL,
    username character varying,
    password character(32),
    enabled character(1) DEFAULT 't'::bpchar NOT NULL,
    ghost character(1) DEFAULT 'f'::bpchar NOT NULL
);


ALTER TABLE public.users OWNER TO postgres;

--
-- TOC entry 1978 (class 1259 OID 20753)
-- Dependencies: 6
-- Name: usersconfigs; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE usersconfigs (
    id integer NOT NULL,
    userid integer,
    configid integer,
    val character varying
);


ALTER TABLE public.usersconfigs OWNER TO postgres;

--
-- TOC entry 1979 (class 1259 OID 20759)
-- Dependencies: 6
-- Name: usersgroups; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE usersgroups (
    id integer NOT NULL,
    groupid integer,
    userid integer
);


ALTER TABLE public.usersgroups OWNER TO postgres;

--
-- TOC entry 715 (class 1255 OID 20762)
-- Dependencies: 6
-- Name: array_accum(anyelement); Type: AGGREGATE; Schema: public; Owner: postgres
--

CREATE AGGREGATE array_accum(anyelement) (
    SFUNC = array_append,
    STYPE = anyarray,
    INITCOND = '{}'
);


ALTER AGGREGATE public.array_accum(anyelement) OWNER TO postgres;

--
-- TOC entry 1980 (class 1259 OID 20763)
-- Dependencies: 2191 6
-- Name: v_audio_adverts; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_audio_adverts AS
    SELECT audio.id, audio.md5, audio.title, archives.id AS archiveid, archives.name AS archive, archives.localpath AS path, dir.id AS dirid, dir.name AS dir, companies.name AS company, audio.advert_description AS description, audio.length_smpl, audio.start_smpl, audio.end_smpl, audio.intro_smpl, audio.extro_smpl, lifespans.data AS lifespan, 'f'::character(1) AS sustainer, audio.filetype FROM audio, archives, audiodir, dir, lifespans, companies WHERE ((((((archives.id = audio.archive) AND (audio.type = 3)) AND (audiodir.audioid = audio.id)) AND (audiodir.dirid = dir.id)) AND (audio.lifespan = lifespans.id)) AND (audio.advert_company = companies.id)) ORDER BY audio.md5;


ALTER TABLE public.v_audio_adverts OWNER TO postgres;

--
-- TOC entry 1981 (class 1259 OID 20768)
-- Dependencies: 2192 6
-- Name: v_audio_jingles; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_audio_jingles AS
    SELECT audio.id, audio.md5, audio.title, archives.id AS archiveid, archives.name AS archive, archives.localpath AS path, jinglepkgs.name AS pkg, jinglepkgs.enabled, jingletypes.name AS type, dir.id AS dirid, dir.name AS dir, audio.length_smpl, audio.start_smpl, audio.end_smpl, audio.intro_smpl, audio.extro_smpl, lifespans.data AS lifespan, audio.filetype FROM audio, archives, audiojinglepkgs, jinglepkgs, jingletypes, audiodir, dir, lifespans WHERE ((((((((archives.id = audio.archive) AND (audio.type = 2)) AND (jinglepkgs.id = audiojinglepkgs.jinglepkgid)) AND (audiojinglepkgs.audioid = audio.id)) AND (audiojinglepkgs.jingletypeid = jingletypes.id)) AND (audiodir.audioid = audio.id)) AND (audiodir.dirid = dir.id)) AND (audio.lifespan = lifespans.id)) ORDER BY audio.md5;


ALTER TABLE public.v_audio_jingles OWNER TO postgres;

--
-- TOC entry 1982 (class 1259 OID 20773)
-- Dependencies: 2193 6
-- Name: v_audio_music; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_audio_music AS
    SELECT audio.id, audio.md5, audio.title, array_to_string(array_accum(artists.name), '; '::text) AS artist, albums.name AS album, archives.id AS archiveid, archives.name AS archive, archives.localpath AS path, audio.music_track AS track, audio.music_released AS released, audio.origin, audio.censor, audiodir.dirid AS dir, audio.length_smpl, audio.start_smpl, audio.end_smpl, audio.intro_smpl, audio.extro_smpl, lifespans.data AS lifespan, audio.sustainer, audio.filetype FROM audio, audioartists, artists, albums, archives, lifespans, audiodir, dir WHERE (((((((((audioartists.audioid = audio.id) AND (audioartists.artistid = artists.id)) AND (audio.archive = archives.id)) AND (audio.music_album = albums.id)) AND (audio.lifespan = lifespans.id)) AND (audiodir.audioid = audio.id)) AND (audiodir.dirid = dir.id)) AND (audiodir.linktype = 0)) AND (audio.type = 1)) GROUP BY audio.md5, audio.id, audio.title, albums.name, archives.id, archives.name, archives.localpath, audio.music_track, audio.music_released, audio.origin, audio.censor, audiodir.dirid, audio.length_smpl, audio.start_smpl, audio.end_smpl, audio.intro_smpl, audio.extro_smpl, lifespans.data, audio.sustainer, audio.filetype ORDER BY audio.md5;


ALTER TABLE public.v_audio_music OWNER TO postgres;

--
-- TOC entry 1983 (class 1259 OID 20778)
-- Dependencies: 2194 6
-- Name: v_audio_prerec; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_audio_prerec AS
    SELECT audio.id, audio.md5, audio.title, array_to_string(array_accum(artists.name), ', '::text) AS artist, albums.name AS album, archives.id AS archiveid, archives.name AS archive, archives.localpath AS path, audio.music_track AS track, audio.music_released AS released, audio.origin, audio.censor, audiodir.dirid AS dir, audio.length_smpl, audio.start_smpl, audio.end_smpl, audio.intro_smpl, audio.extro_smpl, lifespans.data AS lifespan, audio.sustainer, audio.filetype FROM audio, audioartists, artists, albums, archives, lifespans, audiodir, dir WHERE (((((((((audioartists.audioid = audio.id) AND (audioartists.artistid = artists.id)) AND (audio.archive = archives.id)) AND (audio.music_album = albums.id)) AND (audio.lifespan = lifespans.id)) AND (audiodir.audioid = audio.id)) AND (audiodir.dirid = dir.id)) AND (audiodir.linktype = 0)) AND (audio.type = 4)) GROUP BY audio.md5, audio.id, audio.title, albums.name, archives.id, archives.name, archives.localpath, audio.music_track, audio.music_released, audio.origin, audio.censor, audiodir.dirid, audio.length_smpl, audio.start_smpl, audio.end_smpl, audio.intro_smpl, audio.extro_smpl, lifespans.data, audio.sustainer, audio.filetype ORDER BY audio.md5;


ALTER TABLE public.v_audio_prerec OWNER TO postgres;

--
-- TOC entry 1984 (class 1259 OID 20783)
-- Dependencies: 2195 6
-- Name: v_audio; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_audio AS
    ((SELECT 'Music'::character varying AS audiotype, v_audio_music.id, v_audio_music.md5, v_audio_music.title, v_audio_music.artist, v_audio_music.album, v_audio_music.archiveid, v_audio_music.archive, v_audio_music.path, v_audio_music.track, v_audio_music.released, v_audio_music.length_smpl, v_audio_music.start_smpl, v_audio_music.end_smpl, v_audio_music.intro_smpl, v_audio_music.extro_smpl, v_audio_music.lifespan, v_audio_music.sustainer, v_audio_music.filetype FROM v_audio_music UNION SELECT 'Jingle'::character varying AS audiotype, v_audio_jingles.id, v_audio_jingles.md5, v_audio_jingles.title, '' AS artist, v_audio_jingles.pkg AS album, v_audio_jingles.archiveid, v_audio_jingles.archive, v_audio_jingles.path, '0' AS track, '0' AS released, v_audio_jingles.length_smpl, v_audio_jingles.start_smpl, v_audio_jingles.end_smpl, v_audio_jingles.intro_smpl, v_audio_jingles.extro_smpl, v_audio_jingles.lifespan, v_audio_jingles.enabled AS sustainer, v_audio_jingles.filetype FROM v_audio_jingles) UNION SELECT 'Advert'::character varying AS audiotype, v_audio_adverts.id, v_audio_adverts.md5, v_audio_adverts.title, '' AS artist, v_audio_adverts.company AS album, v_audio_adverts.archiveid, v_audio_adverts.archive, v_audio_adverts.path, '0' AS track, '0' AS released, v_audio_adverts.length_smpl, v_audio_adverts.start_smpl, v_audio_adverts.end_smpl, v_audio_adverts.intro_smpl, v_audio_adverts.extro_smpl, v_audio_adverts.lifespan, v_audio_adverts.sustainer, v_audio_adverts.filetype FROM v_audio_adverts) UNION SELECT 'Prerec'::character varying AS audiotype, v_audio_prerec.id, v_audio_prerec.md5, v_audio_prerec.title, v_audio_prerec.artist, v_audio_prerec.album, v_audio_prerec.archiveid, v_audio_prerec.archive, v_audio_prerec.path, '0' AS track, '0' AS released, v_audio_prerec.length_smpl, v_audio_prerec.start_smpl, v_audio_prerec.end_smpl, v_audio_prerec.intro_smpl, v_audio_prerec.extro_smpl, v_audio_prerec.lifespan, v_audio_prerec.sustainer, v_audio_prerec.filetype FROM v_audio_prerec ORDER BY 2;


ALTER TABLE public.v_audio OWNER TO postgres;

--
-- TOC entry 1985 (class 1259 OID 20788)
-- Dependencies: 2196 6
-- Name: v_audiowalls; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_audiowalls AS
    SELECT audio.md5, archives.localpath AS path, audio.start_smpl AS start, audio.end_smpl AS "end", aw_items.item, aw_items.text, aw_walls.name AS wall_name, aw_walls.description AS wall_desc, aw_walls.page, aw_sets.id AS set_id, aw_sets.name AS set, aw_sets.description AS set_desc, aw_props.name AS prop_name, aw_styles_props.value AS prop_value FROM audio, aw_items, aw_walls, aw_sets, aw_styles, aw_styles_props, aw_props, archives WHERE (((((((aw_items.audio_id = audio.id) AND (aw_items.wall_id = aw_walls.id)) AND (aw_walls.set_id = aw_sets.id)) AND (aw_items.style_id = aw_styles.id)) AND (aw_styles_props.style_id = aw_styles.id)) AND (aw_styles_props.prop_id = aw_props.id)) AND (audio.archive = archives.id)) ORDER BY aw_walls.id, aw_items.item, aw_props.id;


ALTER TABLE public.v_audiowalls OWNER TO postgres;

--
-- TOC entry 1986 (class 1259 OID 20792)
-- Dependencies: 2197 6
-- Name: v_cartwalls; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_cartwalls AS
    SELECT audio.md5, archives.localpath AS path, audio.start_smpl AS start, audio.end_smpl AS "end", cartsaudio.cart, cartsaudio.text, cartwalls.name AS wall_name, cartwalls.description AS wall_desc, cartwalls.page, cartsets.id AS cartset_id, cartsets.name AS cartset, cartsets.description AS cartset_desc, cartproperties.name AS prop_name, cartstyleprops.value AS prop_value FROM audio, cartsaudio, cartwalls, cartsets, cartstyles, cartstyleprops, cartproperties, archives WHERE (((((((cartsaudio.audioid = audio.id) AND (cartsaudio.cartwallid = cartwalls.id)) AND (cartwalls.cartsetid = cartsets.id)) AND (cartsaudio.cartstyleid = cartstyles.id)) AND (cartstyleprops.cartstyleid = cartstyles.id)) AND (cartstyleprops.cartpropertyid = cartproperties.id)) AND (audio.archive = archives.id)) ORDER BY cartwalls.id, cartsaudio.cart, cartproperties.id;


ALTER TABLE public.v_cartwalls OWNER TO postgres;

--
-- TOC entry 1987 (class 1259 OID 20796)
-- Dependencies: 2198 6
-- Name: v_playlists; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_playlists AS
    SELECT audio.id, audio.title, artists.name AS artist, audio.length_smpl, playlists.id AS playlistid, playlists.name AS playlist FROM audio, audioplaylists, playlists, audioartists, artists WHERE ((((audioartists.audioid = audio.id) AND (audioartists.artistid = artists.id)) AND (audioplaylists.audioid = audio.id)) AND (audioplaylists.playlistid = playlists.id)) ORDER BY playlists.id, audio.title;


ALTER TABLE public.v_playlists OWNER TO postgres;

--
-- TOC entry 1988 (class 1259 OID 20800)
-- Dependencies: 2199 6
-- Name: v_scripts; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_scripts AS
    SELECT scripts.id, scripts.name, scripts.contents, scripts.length, users.username AS userid FROM scripts, users WHERE (scripts.userid = users.id) ORDER BY scripts.id;


ALTER TABLE public.v_scripts OWNER TO postgres;

--
-- TOC entry 1989 (class 1259 OID 20804)
-- Dependencies: 2200 6
-- Name: v_showplan; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_showplan AS
    (SELECT showitems.showplanid AS id, showitems."position", audio.id AS key, audio.md5, 'audio'::text AS itemtype, audiotypes.name AS audiotype, showitems.comment FROM audio, audiotypes, showitems WHERE ((showitems.audioid = audio.id) AND (audiotypes.id = audio.type)) UNION SELECT showitems.showplanid AS id, showitems."position", scripts.id AS key, ''::text AS md5, 'script'::text AS itemtype, ''::text AS audiotype, showitems.comment FROM scripts, showitems WHERE (showitems.scriptid = scripts.id)) UNION SELECT showitems.showplanid AS id, showitems."position", showitems.id AS key, ''::text AS md5, 'note'::text AS itemtype, ''::text AS audiotype, showitems.comment FROM showitems WHERE ((showitems.audioid IS NULL) AND (showitems.scriptid IS NULL)) ORDER BY 2;


ALTER TABLE public.v_showplan OWNER TO postgres;

--
-- TOC entry 20 (class 1255 OID 20809)
-- Dependencies: 713 6
-- Name: v_tree_getinherited(bigint, bigint); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION v_tree_getinherited(bigint, bigint) RETURNS bit
    AS $_$
    DECLARE
        int_id ALIAS FOR $1;
        int_userid ALIAS FOR $2;
        result RECORD;
        int_parent int8;
        int_type int8;
        bit_permissions bit(8);
    BEGIN
        SELECT INTO bit_permissions bit_or(permissions) 
                    FROM v_tree_dir_explicit 
                    WHERE id = int_id AND userid = int_userid 
                    GROUP BY id;
        IF NOT FOUND THEN
            RETURN '00000000';
        END IF;
        RETURN bit_permissions;
    END $_$
    LANGUAGE plpgsql;


ALTER FUNCTION public.v_tree_getinherited(bigint, bigint) OWNER TO postgres;

--
-- TOC entry 1990 (class 1259 OID 20810)
-- Dependencies: 2201 6
-- Name: v_tree_advert_explicit; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_advert_explicit AS
    SELECT audio.id, audio.title AS name, audiodir.dirid AS parent, users.id AS userid, users.username, audiousers.permissions, 'user'::text AS causetype, users.id AS cause FROM audio, audiodir, audiousers, users WHERE ((((audiodir.audioid = audio.id) AND (audiousers.audioid = audio.id)) AND (audiousers.userid = users.id)) AND (audio.type = 3)) UNION SELECT audio.id, audio.title AS name, audiodir.dirid AS parent, users.id AS userid, users.username, audiogroups.permissions, 'group'::text AS causetype, groups.id AS cause FROM audio, audiodir, audiogroups, usersgroups, users, groups WHERE ((((((audiodir.audioid = audio.id) AND (audiogroups.audioid = audio.id)) AND (audiogroups.groupid = groups.id)) AND (usersgroups.groupid = groups.id)) AND (usersgroups.userid = users.id)) AND (audio.type = 3)) ORDER BY 1;


ALTER TABLE public.v_tree_advert_explicit OWNER TO postgres;

--
-- TOC entry 1991 (class 1259 OID 20815)
-- Dependencies: 2202 6
-- Name: v_tree_advert_inherited; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_advert_inherited AS
    SELECT audio.id, audio.title AS name, audiodir.dirid AS parent, users.id AS userid, users.username, v_tree_getinherited((audiodir.dirid)::bigint, (users.id)::bigint) AS permissions, 'inherited'::text AS causetype, users.id AS cause FROM ((audio JOIN audiodir ON ((audio.id = audiodir.audioid))) CROSS JOIN users) WHERE (((v_tree_getinherited((audiodir.dirid)::bigint, (users.id)::bigint) <> B'00000000'::"bit") AND (audiodir.inherit = 't'::bpchar)) AND (audio.type = 3));


ALTER TABLE public.v_tree_advert_inherited OWNER TO postgres;

--
-- TOC entry 1992 (class 1259 OID 20820)
-- Dependencies: 2203 6
-- Name: v_tree_advert; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_advert AS
    SELECT q1.id, q1.name, q1.parent, q1.userid, q1.username, bit_or(q1.permissions) AS permissions FROM (SELECT v_tree_advert_explicit.id, v_tree_advert_explicit.name, v_tree_advert_explicit.parent, v_tree_advert_explicit.userid, v_tree_advert_explicit.username, v_tree_advert_explicit.permissions, v_tree_advert_explicit.causetype, v_tree_advert_explicit.cause FROM v_tree_advert_explicit UNION SELECT v_tree_advert_inherited.id, v_tree_advert_inherited.name, v_tree_advert_inherited.parent, v_tree_advert_inherited.userid, v_tree_advert_inherited.username, v_tree_advert_inherited.permissions, v_tree_advert_inherited.causetype, v_tree_advert_inherited.cause FROM v_tree_advert_inherited) q1 GROUP BY q1.id, q1.name, q1.parent, q1.userid, q1.username HAVING (bit_or(q1.permissions) <> B'00000000'::"bit");


ALTER TABLE public.v_tree_advert OWNER TO postgres;

--
-- TOC entry 1993 (class 1259 OID 20824)
-- Dependencies: 2204 6
-- Name: v_tree_aw_sets_explicit; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_aw_sets_explicit AS
    SELECT aw_sets.id, aw_sets.name, aw_sets_dir.dir_id AS parent, users.id AS userid, users.username, aw_sets_users.permissions, 'user'::text AS causetype, users.id AS cause FROM aw_sets, aw_sets_dir, aw_sets_users, users WHERE (((aw_sets_dir.set_id = aw_sets.id) AND (aw_sets_users.set_id = aw_sets.id)) AND (aw_sets_users.user_id = users.id)) UNION SELECT aw_sets.id, aw_sets.name, aw_sets_dir.dir_id AS parent, users.id AS userid, users.username, aw_sets_groups.permissions, 'group'::text AS causetype, groups.id AS cause FROM aw_sets, aw_sets_dir, aw_sets_groups, usersgroups, users, groups WHERE (((((aw_sets_dir.set_id = aw_sets.id) AND (aw_sets_groups.set_id = aw_sets.id)) AND (aw_sets_groups.group_id = groups.id)) AND (usersgroups.groupid = groups.id)) AND (usersgroups.userid = users.id));


ALTER TABLE public.v_tree_aw_sets_explicit OWNER TO postgres;

--
-- TOC entry 1994 (class 1259 OID 20829)
-- Dependencies: 2205 6
-- Name: v_tree_aw_sets_inherited; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_aw_sets_inherited AS
    SELECT aw_sets.id, aw_sets.name, aw_sets_dir.dir_id AS parent, users.id AS userid, users.username, v_tree_getinherited((aw_sets_dir.dir_id)::bigint, (users.id)::bigint) AS permissions, 'inherited'::text AS causetype, users.id AS cause FROM ((aw_sets JOIN aw_sets_dir ON ((aw_sets.id = aw_sets_dir.set_id))) CROSS JOIN users) WHERE ((v_tree_getinherited((aw_sets_dir.dir_id)::bigint, (users.id)::bigint) <> B'00000000'::"bit") AND (aw_sets_dir.inherit = 't'::bpchar));


ALTER TABLE public.v_tree_aw_sets_inherited OWNER TO postgres;

--
-- TOC entry 1995 (class 1259 OID 20833)
-- Dependencies: 2206 6
-- Name: v_tree_aw_sets; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_aw_sets AS
    SELECT q1.id, q1.name, q1.parent, q1.userid, q1.username, bit_or(q1.permissions) AS permissions FROM (SELECT v_tree_aw_sets_explicit.id, v_tree_aw_sets_explicit.name, v_tree_aw_sets_explicit.parent, v_tree_aw_sets_explicit.userid, v_tree_aw_sets_explicit.username, v_tree_aw_sets_explicit.permissions, v_tree_aw_sets_explicit.causetype, v_tree_aw_sets_explicit.cause FROM v_tree_aw_sets_explicit UNION SELECT v_tree_aw_sets_inherited.id, v_tree_aw_sets_inherited.name, v_tree_aw_sets_inherited.parent, v_tree_aw_sets_inherited.userid, v_tree_aw_sets_inherited.username, v_tree_aw_sets_inherited.permissions, v_tree_aw_sets_inherited.causetype, v_tree_aw_sets_inherited.cause FROM v_tree_aw_sets_inherited) q1 GROUP BY q1.id, q1.name, q1.parent, q1.userid, q1.username HAVING (bit_or(q1.permissions) <> B'00000000'::"bit");


ALTER TABLE public.v_tree_aw_sets OWNER TO postgres;

--
-- TOC entry 1996 (class 1259 OID 20837)
-- Dependencies: 2207 6
-- Name: v_tree_dir_explicit; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_dir_explicit AS
    SELECT dir.id, dir.name, dir.parent, users.id AS userid, users.username, dirusers.permissions, 'user'::text AS causetype, users.id AS cause FROM dir, users, dirusers WHERE ((dir.id = dirusers.dirid) AND (dirusers.userid = users.id)) UNION SELECT dir.id, dir.name, dir.parent, users.id AS userid, users.username, dirgroups.permissions, 'group'::text AS causetype, groups.id AS cause FROM dir, groups, dirgroups, usersgroups, users WHERE ((((dir.id = dirgroups.dirid) AND (dirgroups.groupid = groups.id)) AND (usersgroups.groupid = groups.id)) AND (usersgroups.userid = users.id));


ALTER TABLE public.v_tree_dir_explicit OWNER TO postgres;

--
-- TOC entry 1997 (class 1259 OID 20842)
-- Dependencies: 2208 6
-- Name: v_tree_dir_inherited; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_dir_inherited AS
    SELECT dir.id, dir.name, dir.parent, users.id AS userid, users.username, v_tree_getinherited((dir.parent)::bigint, (users.id)::bigint) AS permissions, 'inherited'::text AS causetype, users.id AS cause FROM (dir CROSS JOIN users) WHERE ((v_tree_getinherited((dir.parent)::bigint, (users.id)::bigint) <> B'00000000'::"bit") AND (dir.inherit = 't'::bpchar));


ALTER TABLE public.v_tree_dir_inherited OWNER TO postgres;

--
-- TOC entry 1998 (class 1259 OID 20846)
-- Dependencies: 2209 6
-- Name: v_tree_dir; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_dir AS
    SELECT q1.id, q1.name, q1.parent, q1.userid, q1.username, bit_or(q1.permissions) AS permissions FROM (SELECT v_tree_dir_explicit.id, v_tree_dir_explicit.name, v_tree_dir_explicit.parent, v_tree_dir_explicit.userid, v_tree_dir_explicit.username, v_tree_dir_explicit.permissions, v_tree_dir_explicit.causetype, v_tree_dir_explicit.cause FROM v_tree_dir_explicit UNION SELECT v_tree_dir_inherited.id, v_tree_dir_inherited.name, v_tree_dir_inherited.parent, v_tree_dir_inherited.userid, v_tree_dir_inherited.username, v_tree_dir_inherited.permissions, v_tree_dir_inherited.causetype, v_tree_dir_inherited.cause FROM v_tree_dir_inherited) q1 GROUP BY q1.id, q1.name, q1.parent, q1.userid, q1.username HAVING (bit_or(q1.permissions) <> B'00000000'::"bit");


ALTER TABLE public.v_tree_dir OWNER TO postgres;

--
-- TOC entry 1999 (class 1259 OID 20850)
-- Dependencies: 2210 6
-- Name: v_tree_jingle_explicit; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_jingle_explicit AS
    SELECT audio.id, audio.title AS name, audiodir.dirid AS parent, users.id AS userid, users.username, audiousers.permissions, 'user'::text AS causetype, users.id AS cause FROM audio, audiodir, audiousers, users WHERE ((((audiodir.audioid = audio.id) AND (audiousers.audioid = audio.id)) AND (audiousers.userid = users.id)) AND (audio.type = 2)) UNION SELECT audio.id, audio.title AS name, audiodir.dirid AS parent, users.id AS userid, users.username, audiogroups.permissions, 'group'::text AS causetype, groups.id AS cause FROM audio, audiodir, audiogroups, usersgroups, users, groups WHERE ((((((audiodir.audioid = audio.id) AND (audiogroups.audioid = audio.id)) AND (audiogroups.groupid = groups.id)) AND (usersgroups.groupid = groups.id)) AND (usersgroups.userid = users.id)) AND (audio.type = 2));


ALTER TABLE public.v_tree_jingle_explicit OWNER TO postgres;

--
-- TOC entry 2000 (class 1259 OID 20855)
-- Dependencies: 2211 6
-- Name: v_tree_jingle_inherited; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_jingle_inherited AS
    SELECT audio.id, audio.title AS name, audiodir.dirid AS parent, users.id AS userid, users.username, v_tree_getinherited((audiodir.dirid)::bigint, (users.id)::bigint) AS permissions, 'inherited'::text AS causetype, users.id AS cause FROM ((audio JOIN audiodir ON ((audio.id = audiodir.audioid))) CROSS JOIN users) WHERE (((v_tree_getinherited((audiodir.dirid)::bigint, (users.id)::bigint) <> B'00000000'::"bit") AND (audiodir.inherit = 't'::bpchar)) AND (audio.type = 2));


ALTER TABLE public.v_tree_jingle_inherited OWNER TO postgres;

--
-- TOC entry 2001 (class 1259 OID 20860)
-- Dependencies: 2212 6
-- Name: v_tree_jingle; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_jingle AS
    SELECT q1.id, q1.name, q1.parent, q1.userid, q1.username, bit_or(q1.permissions) AS permissions FROM (SELECT v_tree_jingle_explicit.id, v_tree_jingle_explicit.name, v_tree_jingle_explicit.parent, v_tree_jingle_explicit.userid, v_tree_jingle_explicit.username, v_tree_jingle_explicit.permissions, v_tree_jingle_explicit.causetype, v_tree_jingle_explicit.cause FROM v_tree_jingle_explicit UNION SELECT v_tree_jingle_inherited.id, v_tree_jingle_inherited.name, v_tree_jingle_inherited.parent, v_tree_jingle_inherited.userid, v_tree_jingle_inherited.username, v_tree_jingle_inherited.permissions, v_tree_jingle_inherited.causetype, v_tree_jingle_inherited.cause FROM v_tree_jingle_inherited) q1 GROUP BY q1.id, q1.name, q1.parent, q1.userid, q1.username HAVING (bit_or(q1.permissions) <> B'00000000'::"bit");


ALTER TABLE public.v_tree_jingle OWNER TO postgres;

--
-- TOC entry 2002 (class 1259 OID 20864)
-- Dependencies: 2213 6
-- Name: v_tree_music_explicit; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_music_explicit AS
    SELECT audio.id, audio.title AS name, audiodir.dirid AS parent, users.id AS userid, users.username, audiousers.permissions, 'user'::text AS causetype, users.id AS cause FROM audio, audiodir, audiousers, users WHERE ((((audiodir.audioid = audio.id) AND (audiousers.audioid = audio.id)) AND (audiousers.userid = users.id)) AND (audio.type = 1)) UNION SELECT audio.id, audio.title AS name, audiodir.dirid AS parent, users.id AS userid, users.username, audiogroups.permissions, 'group'::text AS causetype, groups.id AS cause FROM audio, audiodir, audiogroups, usersgroups, users, groups WHERE ((((((audiodir.audioid = audio.id) AND (audiogroups.audioid = audio.id)) AND (audiogroups.groupid = groups.id)) AND (usersgroups.groupid = groups.id)) AND (usersgroups.userid = users.id)) AND (audio.type = 1));


ALTER TABLE public.v_tree_music_explicit OWNER TO postgres;

--
-- TOC entry 2003 (class 1259 OID 20869)
-- Dependencies: 2214 6
-- Name: v_tree_music_inherited; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_music_inherited AS
    SELECT audio.id, audio.title AS name, audiodir.dirid AS parent, users.id AS userid, users.username, v_tree_getinherited((audiodir.dirid)::bigint, (users.id)::bigint) AS permissions, 'inherited'::text AS causetype, users.id AS cause FROM ((audio JOIN audiodir ON ((audio.id = audiodir.audioid))) CROSS JOIN users) WHERE (((v_tree_getinherited((audiodir.dirid)::bigint, (users.id)::bigint) <> B'00000000'::"bit") AND (audiodir.inherit = 't'::bpchar)) AND (audio.type = 1));


ALTER TABLE public.v_tree_music_inherited OWNER TO postgres;

--
-- TOC entry 2004 (class 1259 OID 20874)
-- Dependencies: 2215 6
-- Name: v_tree_music; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_music AS
    SELECT q1.id, q1.name, q1.parent, q1.userid, q1.username, bit_or(q1.permissions) AS permissions FROM (SELECT v_tree_music_explicit.id, v_tree_music_explicit.name, v_tree_music_explicit.parent, v_tree_music_explicit.userid, v_tree_music_explicit.username, v_tree_music_explicit.permissions, v_tree_music_explicit.causetype, v_tree_music_explicit.cause FROM v_tree_music_explicit UNION SELECT v_tree_music_inherited.id, v_tree_music_inherited.name, v_tree_music_inherited.parent, v_tree_music_inherited.userid, v_tree_music_inherited.username, v_tree_music_inherited.permissions, v_tree_music_inherited.causetype, v_tree_music_inherited.cause FROM v_tree_music_inherited) q1 GROUP BY q1.id, q1.name, q1.parent, q1.userid, q1.username HAVING (bit_or(q1.permissions) <> B'00000000'::"bit");


ALTER TABLE public.v_tree_music OWNER TO postgres;

--
-- TOC entry 2005 (class 1259 OID 20878)
-- Dependencies: 2216 6
-- Name: v_tree_prerec_explicit; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_prerec_explicit AS
    SELECT audio.id, audio.title AS name, audiodir.dirid AS parent, users.id AS userid, users.username, audiousers.permissions, 'user'::text AS causetype, users.id AS cause FROM audio, audiodir, audiousers, users WHERE ((((audiodir.audioid = audio.id) AND (audiousers.audioid = audio.id)) AND (audiousers.userid = users.id)) AND (audio.type = 4)) UNION SELECT audio.id, audio.title AS name, audiodir.dirid AS parent, users.id AS userid, users.username, audiogroups.permissions, 'group'::text AS causetype, groups.id AS cause FROM audio, audiodir, audiogroups, usersgroups, users, groups WHERE ((((((audiodir.audioid = audio.id) AND (audiogroups.audioid = audio.id)) AND (audiogroups.groupid = groups.id)) AND (usersgroups.groupid = groups.id)) AND (usersgroups.userid = users.id)) AND (audio.type = 4));


ALTER TABLE public.v_tree_prerec_explicit OWNER TO postgres;

--
-- TOC entry 2006 (class 1259 OID 20883)
-- Dependencies: 2217 6
-- Name: v_tree_prerec_inherited; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_prerec_inherited AS
    SELECT audio.id, audio.title AS name, audiodir.dirid AS parent, users.id AS userid, users.username, v_tree_getinherited((audiodir.dirid)::bigint, (users.id)::bigint) AS permissions, 'inherited'::text AS causetype, users.id AS cause FROM ((audio JOIN audiodir ON ((audio.id = audiodir.audioid))) CROSS JOIN users) WHERE (((v_tree_getinherited((audiodir.dirid)::bigint, (users.id)::bigint) <> B'00000000'::"bit") AND (audiodir.inherit = 't'::bpchar)) AND (audio.type = 4));


ALTER TABLE public.v_tree_prerec_inherited OWNER TO postgres;

--
-- TOC entry 2007 (class 1259 OID 20888)
-- Dependencies: 2218 6
-- Name: v_tree_prerec; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_prerec AS
    SELECT q1.id, q1.name, q1.parent, q1.userid, q1.username, bit_or(q1.permissions) AS permissions FROM (SELECT v_tree_prerec_explicit.id, v_tree_prerec_explicit.name, v_tree_prerec_explicit.parent, v_tree_prerec_explicit.userid, v_tree_prerec_explicit.username, v_tree_prerec_explicit.permissions, v_tree_prerec_explicit.causetype, v_tree_prerec_explicit.cause FROM v_tree_prerec_explicit UNION SELECT v_tree_prerec_inherited.id, v_tree_prerec_inherited.name, v_tree_prerec_inherited.parent, v_tree_prerec_inherited.userid, v_tree_prerec_inherited.username, v_tree_prerec_inherited.permissions, v_tree_prerec_inherited.causetype, v_tree_prerec_inherited.cause FROM v_tree_prerec_inherited) q1 GROUP BY q1.id, q1.name, q1.parent, q1.userid, q1.username HAVING (bit_or(q1.permissions) <> B'00000000'::"bit");


ALTER TABLE public.v_tree_prerec OWNER TO postgres;

--
-- TOC entry 2008 (class 1259 OID 20892)
-- Dependencies: 2219 6
-- Name: v_tree_script_explicit; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_script_explicit AS
    SELECT scripts.id, scripts.name, scriptsdir.dirid AS parent, users.id AS userid, users.username, scriptsusers.permissions, 'user'::text AS causetype, users.id AS cause FROM scripts, scriptsdir, scriptsusers, users WHERE (((scriptsdir.scriptid = scripts.id) AND (scriptsusers.scriptid = scripts.id)) AND (scriptsusers.userid = users.id)) UNION SELECT scripts.id, scripts.name, scriptsdir.dirid AS parent, users.id AS userid, users.username, scriptsgroups.permissions, 'group'::text AS causetype, groups.id AS cause FROM scripts, scriptsdir, scriptsgroups, usersgroups, users, groups WHERE (((((scriptsdir.scriptid = scripts.id) AND (scriptsgroups.scriptid = scripts.id)) AND (scriptsgroups.groupid = groups.id)) AND (usersgroups.groupid = groups.id)) AND (usersgroups.userid = users.id));


ALTER TABLE public.v_tree_script_explicit OWNER TO postgres;

--
-- TOC entry 2009 (class 1259 OID 20897)
-- Dependencies: 2220 6
-- Name: v_tree_script_inherited; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_script_inherited AS
    SELECT scripts.id, scripts.name, scriptsdir.dirid AS parent, users.id AS userid, users.username, v_tree_getinherited((scriptsdir.dirid)::bigint, (users.id)::bigint) AS permissions, 'inherited'::text AS causetype, users.id AS cause FROM ((scripts JOIN scriptsdir ON ((scripts.id = scriptsdir.scriptid))) CROSS JOIN users) WHERE ((v_tree_getinherited((scriptsdir.dirid)::bigint, (users.id)::bigint) <> B'00000000'::"bit") AND (scriptsdir.inherit = 't'::bpchar));


ALTER TABLE public.v_tree_script_inherited OWNER TO postgres;

--
-- TOC entry 2010 (class 1259 OID 20901)
-- Dependencies: 2221 6
-- Name: v_tree_script; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_script AS
    SELECT q1.id, q1.name, q1.parent, q1.userid, q1.username, bit_or(q1.permissions) AS permissions FROM (SELECT v_tree_script_explicit.id, v_tree_script_explicit.name, v_tree_script_explicit.parent, v_tree_script_explicit.userid, v_tree_script_explicit.username, v_tree_script_explicit.permissions, v_tree_script_explicit.causetype, v_tree_script_explicit.cause FROM v_tree_script_explicit UNION SELECT v_tree_script_inherited.id, v_tree_script_inherited.name, v_tree_script_inherited.parent, v_tree_script_inherited.userid, v_tree_script_inherited.username, v_tree_script_inherited.permissions, v_tree_script_inherited.causetype, v_tree_script_inherited.cause FROM v_tree_script_inherited) q1 GROUP BY q1.id, q1.name, q1.parent, q1.userid, q1.username HAVING (bit_or(q1.permissions) <> B'00000000'::"bit");


ALTER TABLE public.v_tree_script OWNER TO postgres;

--
-- TOC entry 2011 (class 1259 OID 20905)
-- Dependencies: 2222 6
-- Name: v_tree_showplan_explicit; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_showplan_explicit AS
    SELECT showplans.id, showplans.name, showplansdir.dirid AS parent, users.id AS userid, users.username, showplansusers.permissions, 'user'::text AS causetype, users.id AS cause FROM showplans, showplansdir, showplansusers, users WHERE (((showplansdir.showplanid = showplans.id) AND (showplansusers.showplanid = showplans.id)) AND (showplansusers.userid = users.id)) UNION SELECT showplans.id, showplans.name, showplansdir.dirid AS parent, users.id AS userid, users.username, showplansgroups.permissions, 'group'::text AS causetype, groups.id AS cause FROM showplans, showplansdir, showplansgroups, usersgroups, users, groups WHERE (((((showplansdir.showplanid = showplans.id) AND (showplansgroups.showplanid = showplans.id)) AND (showplansgroups.groupid = groups.id)) AND (usersgroups.groupid = groups.id)) AND (usersgroups.userid = users.id));


ALTER TABLE public.v_tree_showplan_explicit OWNER TO postgres;

--
-- TOC entry 2012 (class 1259 OID 20910)
-- Dependencies: 2223 6
-- Name: v_tree_showplan_inherited; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_showplan_inherited AS
    SELECT showplans.id, showplans.name, showplansdir.dirid AS parent, users.id AS userid, users.username, v_tree_getinherited((showplansdir.dirid)::bigint, (users.id)::bigint) AS permissions, 'inherited'::text AS causetype, users.id AS cause FROM ((showplans JOIN showplansdir ON ((showplans.id = showplansdir.showplanid))) CROSS JOIN users) WHERE ((v_tree_getinherited((showplansdir.dirid)::bigint, (users.id)::bigint) <> B'00000000'::"bit") AND (showplansdir.inherit = 't'::bpchar));


ALTER TABLE public.v_tree_showplan_inherited OWNER TO postgres;

--
-- TOC entry 2013 (class 1259 OID 20914)
-- Dependencies: 2224 6
-- Name: v_tree_showplan; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_showplan AS
    SELECT q1.id, q1.name, q1.parent, q1.userid, q1.username, bit_or(q1.permissions) AS permissions FROM (SELECT v_tree_showplan_explicit.id, v_tree_showplan_explicit.name, v_tree_showplan_explicit.parent, v_tree_showplan_explicit.userid, v_tree_showplan_explicit.username, v_tree_showplan_explicit.permissions, v_tree_showplan_explicit.causetype, v_tree_showplan_explicit.cause FROM v_tree_showplan_explicit UNION SELECT v_tree_showplan_inherited.id, v_tree_showplan_inherited.name, v_tree_showplan_inherited.parent, v_tree_showplan_inherited.userid, v_tree_showplan_inherited.username, v_tree_showplan_inherited.permissions, v_tree_showplan_inherited.causetype, v_tree_showplan_inherited.cause FROM v_tree_showplan_inherited) q1 GROUP BY q1.id, q1.name, q1.parent, q1.userid, q1.username HAVING (bit_or(q1.permissions) <> B'00000000'::"bit");


ALTER TABLE public.v_tree_showplan OWNER TO postgres;

--
-- TOC entry 2014 (class 1259 OID 20918)
-- Dependencies: 2225 6
-- Name: v_tree; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree AS
    SELECT q1.itemtype, q1.id, q1.name, q1.parent, q1.userid, q1.username, bit_or(q1.permissions) AS permissions FROM (((((((SELECT 'dir' AS itemtype, v_tree_dir.id, v_tree_dir.name, v_tree_dir.parent, v_tree_dir.userid, v_tree_dir.username, v_tree_dir.permissions FROM v_tree_dir UNION SELECT 'aw_set' AS itemtype, v_tree_aw_sets.id, v_tree_aw_sets.name, v_tree_aw_sets.parent, v_tree_aw_sets.userid, v_tree_aw_sets.username, v_tree_aw_sets.permissions FROM v_tree_aw_sets) UNION SELECT 'script' AS itemtype, v_tree_script.id, v_tree_script.name, v_tree_script.parent, v_tree_script.userid, v_tree_script.username, v_tree_script.permissions FROM v_tree_script) UNION SELECT 'music' AS itemtype, v_tree_music.id, v_tree_music.name, v_tree_music.parent, v_tree_music.userid, v_tree_music.username, v_tree_music.permissions FROM v_tree_music) UNION SELECT 'jingle' AS itemtype, v_tree_jingle.id, v_tree_jingle.name, v_tree_jingle.parent, v_tree_jingle.userid, v_tree_jingle.username, v_tree_jingle.permissions FROM v_tree_jingle) UNION SELECT 'prerec' AS itemtype, v_tree_prerec.id, v_tree_prerec.name, v_tree_prerec.parent, v_tree_prerec.userid, v_tree_prerec.username, v_tree_prerec.permissions FROM v_tree_prerec) UNION SELECT 'advert' AS itemtype, v_tree_advert.id, v_tree_advert.name, v_tree_advert.parent, v_tree_advert.userid, v_tree_advert.username, v_tree_advert.permissions FROM v_tree_advert) UNION SELECT 'showplan' AS itemtype, v_tree_showplan.id, v_tree_showplan.name, v_tree_showplan.parent, v_tree_showplan.userid, v_tree_showplan.username, v_tree_showplan.permissions FROM v_tree_showplan) q1 GROUP BY q1.itemtype, q1.name, q1.id, q1.parent, q1.userid, q1.username HAVING (bit_or(q1.permissions) <> B'00000000'::"bit") ORDER BY q1.itemtype, q1.name;


ALTER TABLE public.v_tree OWNER TO postgres;

--
-- TOC entry 2015 (class 1259 OID 20923)
-- Dependencies: 2226 6
-- Name: v_tree_audio; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_audio AS
    SELECT q1.itemtype, q1.id, q1.name, q1.parent, q1.userid, q1.username, bit_or(q1.permissions) AS permissions FROM (((SELECT 'music' AS itemtype, v_tree_music.id, v_tree_music.name, v_tree_music.parent, v_tree_music.userid, v_tree_music.username, v_tree_music.permissions FROM v_tree_music UNION SELECT 'jingle' AS itemtype, v_tree_jingle.id, v_tree_jingle.name, v_tree_jingle.parent, v_tree_jingle.userid, v_tree_jingle.username, v_tree_jingle.permissions FROM v_tree_jingle) UNION SELECT 'prerec' AS itemtype, v_tree_prerec.id, v_tree_prerec.name, v_tree_prerec.parent, v_tree_prerec.userid, v_tree_prerec.username, v_tree_prerec.permissions FROM v_tree_prerec) UNION SELECT 'advert' AS itemtype, v_tree_advert.id, v_tree_advert.name, v_tree_advert.parent, v_tree_advert.userid, v_tree_advert.username, v_tree_advert.permissions FROM v_tree_advert) q1 GROUP BY q1.itemtype, q1.name, q1.id, q1.parent, q1.userid, q1.username HAVING (bit_or(q1.permissions) <> B'00000000'::"bit") ORDER BY q1.itemtype, q1.name;


ALTER TABLE public.v_tree_audio OWNER TO postgres;

--
-- TOC entry 2016 (class 1259 OID 20927)
-- Dependencies: 2227 6
-- Name: v_tree_cartset_explicit; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_cartset_explicit AS
    SELECT cartsets.id, cartsets.name, cartsetsdir.dirid AS parent, users.id AS userid, users.username, cartsetsusers.permissions, 'user'::text AS causetype, users.id AS cause FROM cartsets, cartsetsdir, cartsetsusers, users WHERE (((cartsetsdir.cartsetid = cartsets.id) AND (cartsetsusers.cartsetid = cartsets.id)) AND (cartsetsusers.userid = users.id)) UNION SELECT cartsets.id, cartsets.name, cartsetsdir.dirid AS parent, users.id AS userid, users.username, cartsetsgroups.permissions, 'group'::text AS causetype, groups.id AS cause FROM cartsets, cartsetsdir, cartsetsgroups, usersgroups, users, groups WHERE (((((cartsetsdir.cartsetid = cartsets.id) AND (cartsetsgroups.cartsetid = cartsets.id)) AND (cartsetsgroups.groupid = groups.id)) AND (usersgroups.groupid = groups.id)) AND (usersgroups.userid = users.id));


ALTER TABLE public.v_tree_cartset_explicit OWNER TO postgres;

--
-- TOC entry 2017 (class 1259 OID 20932)
-- Dependencies: 2228 6
-- Name: v_tree_cartset_inherited; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_cartset_inherited AS
    SELECT cartsets.id, cartsets.name, cartsetsdir.dirid AS parent, users.id AS userid, users.username, v_tree_getinherited((cartsetsdir.dirid)::bigint, (users.id)::bigint) AS permissions, 'inherited'::text AS causetype, users.id AS cause FROM ((cartsets JOIN cartsetsdir ON ((cartsets.id = cartsetsdir.cartsetid))) CROSS JOIN users) WHERE ((v_tree_getinherited((cartsetsdir.dirid)::bigint, (users.id)::bigint) <> B'00000000'::"bit") AND (cartsetsdir.inherit = 't'::bpchar));


ALTER TABLE public.v_tree_cartset_inherited OWNER TO postgres;

--
-- TOC entry 2018 (class 1259 OID 20936)
-- Dependencies: 2229 6
-- Name: v_tree_cartset; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW v_tree_cartset AS
    SELECT q1.id, q1.name, q1.parent, q1.userid, q1.username, bit_or(q1.permissions) AS permissions FROM (SELECT v_tree_cartset_explicit.id, v_tree_cartset_explicit.name, v_tree_cartset_explicit.parent, v_tree_cartset_explicit.userid, v_tree_cartset_explicit.username, v_tree_cartset_explicit.permissions, v_tree_cartset_explicit.causetype, v_tree_cartset_explicit.cause FROM v_tree_cartset_explicit UNION SELECT v_tree_cartset_inherited.id, v_tree_cartset_inherited.name, v_tree_cartset_inherited.parent, v_tree_cartset_inherited.userid, v_tree_cartset_inherited.username, v_tree_cartset_inherited.permissions, v_tree_cartset_inherited.causetype, v_tree_cartset_inherited.cause FROM v_tree_cartset_inherited) q1 GROUP BY q1.id, q1.name, q1.parent, q1.userid, q1.username HAVING (bit_or(q1.permissions) <> B'00000000'::"bit");


ALTER TABLE public.v_tree_cartset OWNER TO postgres;

--
-- TOC entry 21 (class 1255 OID 20940)
-- Dependencies: 713 6
-- Name: f_audio_delete(); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION f_audio_delete() RETURNS trigger
    AS $$
	BEGIN
		DELETE FROM audiodir WHERE audioid = OLD.id;
		DELETE FROM audiogroups WHERE audioid = OLD.id;
		DELETE FROM audiousers WHERE audioid = OLD.id;
		DELETE FROM audioplaylists WHERE audioid = OLD.id;
		DELETE FROM audiolog WHERE audioid = OLD.id;
		DELETE FROM audiocomments WHERE audioid = OLD.id;
		DELETE FROM advertschedule WHERE audioid = OLD.id;
		DELETE FROM audioartists WHERE audioid = OLD.id;
		DELETE FROM audiokeywords WHERE audioid = OLD.id;
		DELETE FROM audiojinglepkgs WHERE audioid = OLD.id;
		DELETE FROM aw_items WHERE audio_id = OLD.id;
		UPDATE showitems SET audioid = NULL WHERE audioid = OLD.id;
		DELETE FROM binsaudio WHERE audioid = OLD.id;
		RETURN OLD;
	END $$
    LANGUAGE plpgsql;


ALTER FUNCTION public.f_audio_delete() OWNER TO postgres;

--
-- TOC entry 22 (class 1255 OID 20941)
-- Dependencies: 713 6
-- Name: f_aw_props_delete(); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION f_aw_props_delete() RETURNS trigger
    AS $$
	BEGIN
		DELETE FROM aw_style_props WHERE style_id = OLD.id;
		RETURN OLD;
	END $$
    LANGUAGE plpgsql;


ALTER FUNCTION public.f_aw_props_delete() OWNER TO postgres;

--
-- TOC entry 23 (class 1255 OID 20942)
-- Dependencies: 6 713
-- Name: f_aw_sets_delete(); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION f_aw_sets_delete() RETURNS trigger
    AS $$ 
	BEGIN
		DELETE FROM aw_walls WHERE set_id = OLD.id;
		DELETE FROM aw_sets_users WHERE set_id = OLD.id;
		DELETE FROM aw_sets_groups WHERE set_id = OLD.id;
		DELETE FROM aw_sets_dir WHERE set_id = OLD.id;
        DELETE FROM usersconfigs USING configs 
            WHERE configs.id = usersconfigs.configid
            AND configs.name = 'default_aw_set'
            AND usersconfigs.val = CAST(OLD.id AS VARCHAR);
		RETURN OLD;
	END $$
    LANGUAGE plpgsql;


ALTER FUNCTION public.f_aw_sets_delete() OWNER TO postgres;

--
-- TOC entry 24 (class 1255 OID 20943)
-- Dependencies: 713 6
-- Name: f_aw_styles_delete(); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION f_aw_styles_delete() RETURNS trigger
    AS $$
	DECLARE
		styles RECORD;
	BEGIN
		DELETE FROM aw_style_props WHERE style_id = OLD.id;
		SELECT INTO styles id FROM aw_styles WHERE id != OLD.id LIMIT 1;
		IF NOT FOUND THEN
			RAISE EXCEPTION 'Cannot delete last style %!', OLD.name;
			RETURN NULL;
		END IF;
		UPDATE aw_items SET style_id = styles.id WHERE style_id = OLD.id;
		RETURN OLD;
	END $$
    LANGUAGE plpgsql;


ALTER FUNCTION public.f_aw_styles_delete() OWNER TO postgres;

--
-- TOC entry 25 (class 1255 OID 20944)
-- Dependencies: 713 6
-- Name: f_aw_walls_delete(); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION f_aw_walls_delete() RETURNS trigger
    AS $$ 
	BEGIN
		DELETE FROM aw_items WHERE wall_id = OLD.id;
		RETURN OLD;
	END	$$
    LANGUAGE plpgsql;


ALTER FUNCTION public.f_aw_walls_delete() OWNER TO postgres;

--
-- TOC entry 26 (class 1255 OID 20945)
-- Dependencies: 713 6
-- Name: f_dir_delete(); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION f_dir_delete() RETURNS trigger
    AS $$
	DECLARE
		audio_keys RECORD;
	BEGIN
		FOR audio_keys IN SELECT audioid FROM audiodir WHERE dirid = OLD.id AND linktype = 0 LOOP
			DELETE FROM AUDIO WHERE id = audio_keys.audioid;
		END LOOP;
		DELETE FROM audiodir WHERE id = OLD.id;
		DELETE FROM dirusers WHERE dirid = OLD.id;
		DELETE FROM dirgroups WHERE dirid = OLD.id;
		RETURN OLD;
	END $$
    LANGUAGE plpgsql;


ALTER FUNCTION public.f_dir_delete() OWNER TO postgres;

--
-- TOC entry 27 (class 1255 OID 20946)
-- Dependencies: 713 6
-- Name: f_groups_delete(); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION f_groups_delete() RETURNS trigger
    AS $$
	BEGIN
		DELETE FROM dirgroups WHERE groupid = OLD.id;
		DELETE FROM usersgroups WHERE groupid = OLD.id;
		DELETE FROM aw_sets_groups WHERE group_id = OLD.id;		
		DELETE FROM audiogroups WHERE groupid = OLD.id;
		RETURN OLD;
	END $$
    LANGUAGE plpgsql;


ALTER FUNCTION public.f_groups_delete() OWNER TO postgres;

--
-- TOC entry 28 (class 1255 OID 20947)
-- Dependencies: 713 6
-- Name: f_scripts_delete(); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION f_scripts_delete() RETURNS trigger
    AS $$
	BEGIN
		UPDATE showitems SET scriptid = NULL WHERE scriptid = OLD.id;
		DELETE FROM scriptsdir WHERE scriptid = OLD.id;
		DELETE FROM scriptsusers WHERE scriptid = OLD.id;
		DELETE FROM scriptsgroups WHERE scriptid = OLD.id;
		RETURN OLD;
	END $$
    LANGUAGE plpgsql;


ALTER FUNCTION public.f_scripts_delete() OWNER TO postgres;

--
-- TOC entry 29 (class 1255 OID 20948)
-- Dependencies: 713 6
-- Name: f_showplans_delete(); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION f_showplans_delete() RETURNS trigger
    AS $$
	BEGIN
		DELETE FROM showitems WHERE showplanid = OLD.id;
		DELETE FROM showplansdir WHERE showplanid = OLD.id;
		DELETE FROM showplansusers WHERE showplanid = OLD.id;
		DELETE FROM showplansgroups WHERE showplanid = OLD.id;
		RETURN OLD;
	END $$
    LANGUAGE plpgsql;


ALTER FUNCTION public.f_showplans_delete() OWNER TO postgres;

--
-- TOC entry 30 (class 1255 OID 20949)
-- Dependencies: 713 6
-- Name: f_user_required(integer); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION f_user_required(integer) RETURNS boolean
    AS $_$
	DECLARE
		temp RECORD;
	BEGIN
		SELECT INTO temp * FROM audio WHERE audio.creator = $1;
		IF FOUND THEN
			RETURN TRUE;
		END IF;
		SELECT INTO temp * FROM audiolog WHERE userid = $1;
		IF FOUND THEN
			RETURN TRUE;
		END IF;
		SELECT INTO temp * FROM audiocomments WHERE userid = $1;
		IF FOUND THEN
			RETURN TRUE;
		END IF;
		RETURN FALSE;
	END $_$
    LANGUAGE plpgsql;


ALTER FUNCTION public.f_user_required(integer) OWNER TO postgres;

--
-- TOC entry 31 (class 1255 OID 20950)
-- Dependencies: 6 713
-- Name: f_users_delete(); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION f_users_delete() RETURNS trigger
    AS $$
	BEGIN
		DELETE FROM usersconfigs WHERE userid = OLD.id;
		DELETE FROM dirusers WHERE userid = OLD.id;
		DELETE FROM scriptsusers WHERE userid = OLD.id;
		DELETE FROM showplanusers WHERE userid = OLD.id;
		DELETE FROM usersgroups WHERE userid = OLD.id;
		DELETE FROM aw_sets_users WHERE user_id = OLD.id;
		DELETE FROM audiousers WHERE userid = OLD.id;
		IF f_user_required(OLD.id) THEN
			UPDATE users SET ghost = 't' WHERE id = OLD.id;
			RETURN NULL;
		END IF;
		RETURN OLD;
	END $$
    LANGUAGE plpgsql;


ALTER FUNCTION public.f_users_delete() OWNER TO postgres;

--
-- TOC entry 2019 (class 1259 OID 20951)
-- Dependencies: 6 1887
-- Name: advertschedule_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE advertschedule_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.advertschedule_id_seq OWNER TO postgres;

--
-- TOC entry 3044 (class 0 OID 0)
-- Dependencies: 2019
-- Name: advertschedule_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE advertschedule_id_seq OWNED BY advertschedule.id;


--
-- TOC entry 2020 (class 1259 OID 20953)
-- Dependencies: 1888 6
-- Name: albums_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE albums_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.albums_id_seq OWNER TO postgres;

--
-- TOC entry 3046 (class 0 OID 0)
-- Dependencies: 2020
-- Name: albums_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE albums_id_seq OWNED BY albums.id;


--
-- TOC entry 2021 (class 1259 OID 20955)
-- Dependencies: 1889 6
-- Name: archives_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE archives_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.archives_id_seq OWNER TO postgres;

--
-- TOC entry 3048 (class 0 OID 0)
-- Dependencies: 2021
-- Name: archives_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE archives_id_seq OWNED BY archives.id;


--
-- TOC entry 2022 (class 1259 OID 20957)
-- Dependencies: 1890 6
-- Name: artists_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE artists_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.artists_id_seq OWNER TO postgres;

--
-- TOC entry 3050 (class 0 OID 0)
-- Dependencies: 2022
-- Name: artists_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE artists_id_seq OWNED BY artists.id;


--
-- TOC entry 2023 (class 1259 OID 20959)
-- Dependencies: 6 1891
-- Name: artistskeywords_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE artistskeywords_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.artistskeywords_id_seq OWNER TO postgres;

--
-- TOC entry 3052 (class 0 OID 0)
-- Dependencies: 2023
-- Name: artistskeywords_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE artistskeywords_id_seq OWNED BY artistskeywords.id;


--
-- TOC entry 2024 (class 1259 OID 20961)
-- Dependencies: 6 1892
-- Name: audio_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE audio_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.audio_id_seq OWNER TO postgres;

--
-- TOC entry 3054 (class 0 OID 0)
-- Dependencies: 2024
-- Name: audio_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE audio_id_seq OWNED BY audio.id;


--
-- TOC entry 2025 (class 1259 OID 20963)
-- Dependencies: 1893 6
-- Name: audioartists_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE audioartists_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.audioartists_id_seq OWNER TO postgres;

--
-- TOC entry 3056 (class 0 OID 0)
-- Dependencies: 2025
-- Name: audioartists_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE audioartists_id_seq OWNED BY audioartists.id;


--
-- TOC entry 2026 (class 1259 OID 20965)
-- Dependencies: 1894 6
-- Name: audiocomments_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE audiocomments_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.audiocomments_id_seq OWNER TO postgres;

--
-- TOC entry 3058 (class 0 OID 0)
-- Dependencies: 2026
-- Name: audiocomments_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE audiocomments_id_seq OWNED BY audiocomments.id;


--
-- TOC entry 2027 (class 1259 OID 20967)
-- Dependencies: 1895 6
-- Name: audiodir_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE audiodir_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.audiodir_id_seq OWNER TO postgres;

--
-- TOC entry 3060 (class 0 OID 0)
-- Dependencies: 2027
-- Name: audiodir_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE audiodir_id_seq OWNED BY audiodir.id;


--
-- TOC entry 2028 (class 1259 OID 20969)
-- Dependencies: 6 1896
-- Name: audioext_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE audioext_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.audioext_id_seq OWNER TO postgres;

--
-- TOC entry 3062 (class 0 OID 0)
-- Dependencies: 2028
-- Name: audioext_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE audioext_id_seq OWNED BY audioext.id;


--
-- TOC entry 2029 (class 1259 OID 20971)
-- Dependencies: 6 1897
-- Name: audiogroups_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE audiogroups_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.audiogroups_id_seq OWNER TO postgres;

--
-- TOC entry 3064 (class 0 OID 0)
-- Dependencies: 2029
-- Name: audiogroups_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE audiogroups_id_seq OWNED BY audiogroups.id;


--
-- TOC entry 2030 (class 1259 OID 20973)
-- Dependencies: 1898 6
-- Name: audiojinglepkgs_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE audiojinglepkgs_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.audiojinglepkgs_id_seq OWNER TO postgres;

--
-- TOC entry 3066 (class 0 OID 0)
-- Dependencies: 2030
-- Name: audiojinglepkgs_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE audiojinglepkgs_id_seq OWNED BY audiojinglepkgs.id;


--
-- TOC entry 2031 (class 1259 OID 20975)
-- Dependencies: 6 1899
-- Name: audiokeywords_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE audiokeywords_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.audiokeywords_id_seq OWNER TO postgres;

--
-- TOC entry 3068 (class 0 OID 0)
-- Dependencies: 2031
-- Name: audiokeywords_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE audiokeywords_id_seq OWNED BY audiokeywords.id;


--
-- TOC entry 2032 (class 1259 OID 20977)
-- Dependencies: 6 1900
-- Name: audiolog_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE audiolog_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.audiolog_id_seq OWNER TO postgres;

--
-- TOC entry 3070 (class 0 OID 0)
-- Dependencies: 2032
-- Name: audiolog_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE audiolog_id_seq OWNED BY audiolog.id;


--
-- TOC entry 2033 (class 1259 OID 20979)
-- Dependencies: 6 1901
-- Name: audioplaylists_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE audioplaylists_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.audioplaylists_id_seq OWNER TO postgres;

--
-- TOC entry 3072 (class 0 OID 0)
-- Dependencies: 2033
-- Name: audioplaylists_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE audioplaylists_id_seq OWNED BY audioplaylists.id;


--
-- TOC entry 2034 (class 1259 OID 20981)
-- Dependencies: 1902 6
-- Name: audiotypes_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE audiotypes_id_seq
    START WITH 5
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.audiotypes_id_seq OWNER TO postgres;

--
-- TOC entry 3074 (class 0 OID 0)
-- Dependencies: 2034
-- Name: audiotypes_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE audiotypes_id_seq OWNED BY audiotypes.id;


--
-- TOC entry 2035 (class 1259 OID 20983)
-- Dependencies: 1903 6
-- Name: audiousers_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE audiousers_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.audiousers_id_seq OWNER TO postgres;

--
-- TOC entry 3076 (class 0 OID 0)
-- Dependencies: 2035
-- Name: audiousers_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE audiousers_id_seq OWNED BY audiousers.id;


--
-- TOC entry 2036 (class 1259 OID 20985)
-- Dependencies: 1904 6
-- Name: aw_items_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE aw_items_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.aw_items_id_seq OWNER TO postgres;

--
-- TOC entry 3078 (class 0 OID 0)
-- Dependencies: 2036
-- Name: aw_items_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE aw_items_id_seq OWNED BY aw_items.id;


--
-- TOC entry 2037 (class 1259 OID 20987)
-- Dependencies: 1905 6
-- Name: aw_props_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE aw_props_id_seq
    START WITH 7
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.aw_props_id_seq OWNER TO postgres;

--
-- TOC entry 3080 (class 0 OID 0)
-- Dependencies: 2037
-- Name: aw_props_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE aw_props_id_seq OWNED BY aw_props.id;


--
-- TOC entry 2038 (class 1259 OID 20989)
-- Dependencies: 1907 6
-- Name: aw_sets_dir_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE aw_sets_dir_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.aw_sets_dir_id_seq OWNER TO postgres;

--
-- TOC entry 3082 (class 0 OID 0)
-- Dependencies: 2038
-- Name: aw_sets_dir_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE aw_sets_dir_id_seq OWNED BY aw_sets_dir.id;


--
-- TOC entry 2039 (class 1259 OID 20991)
-- Dependencies: 6 1908
-- Name: aw_sets_groups_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE aw_sets_groups_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.aw_sets_groups_id_seq OWNER TO postgres;

--
-- TOC entry 3084 (class 0 OID 0)
-- Dependencies: 2039
-- Name: aw_sets_groups_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE aw_sets_groups_id_seq OWNED BY aw_sets_groups.id;


--
-- TOC entry 2040 (class 1259 OID 20993)
-- Dependencies: 1906 6
-- Name: aw_sets_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE aw_sets_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.aw_sets_id_seq OWNER TO postgres;

--
-- TOC entry 3086 (class 0 OID 0)
-- Dependencies: 2040
-- Name: aw_sets_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE aw_sets_id_seq OWNED BY aw_sets.id;


--
-- TOC entry 2041 (class 1259 OID 20995)
-- Dependencies: 1909 6
-- Name: aw_sets_users_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE aw_sets_users_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.aw_sets_users_id_seq OWNER TO postgres;

--
-- TOC entry 3088 (class 0 OID 0)
-- Dependencies: 2041
-- Name: aw_sets_users_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE aw_sets_users_id_seq OWNED BY aw_sets_users.id;


--
-- TOC entry 2042 (class 1259 OID 20997)
-- Dependencies: 6 1910
-- Name: aw_styles_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE aw_styles_id_seq
    START WITH 5
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.aw_styles_id_seq OWNER TO postgres;

--
-- TOC entry 3090 (class 0 OID 0)
-- Dependencies: 2042
-- Name: aw_styles_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE aw_styles_id_seq OWNED BY aw_styles.id;


--
-- TOC entry 2043 (class 1259 OID 20999)
-- Dependencies: 1911 6
-- Name: aw_styles_props_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE aw_styles_props_id_seq
    START WITH 9
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.aw_styles_props_id_seq OWNER TO postgres;

--
-- TOC entry 3092 (class 0 OID 0)
-- Dependencies: 2043
-- Name: aw_styles_props_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE aw_styles_props_id_seq OWNED BY aw_styles_props.id;


--
-- TOC entry 2044 (class 1259 OID 21001)
-- Dependencies: 6 1912
-- Name: aw_walls_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE aw_walls_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.aw_walls_id_seq OWNER TO postgres;

--
-- TOC entry 3094 (class 0 OID 0)
-- Dependencies: 2044
-- Name: aw_walls_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE aw_walls_id_seq OWNED BY aw_walls.id;


--
-- TOC entry 2045 (class 1259 OID 21003)
-- Dependencies: 6 1913
-- Name: bins_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE bins_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.bins_id_seq OWNER TO postgres;

--
-- TOC entry 3096 (class 0 OID 0)
-- Dependencies: 2045
-- Name: bins_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE bins_id_seq OWNED BY bins.id;


--
-- TOC entry 2046 (class 1259 OID 21005)
-- Dependencies: 6 1914
-- Name: binsartists_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE binsartists_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.binsartists_id_seq OWNER TO postgres;

--
-- TOC entry 3098 (class 0 OID 0)
-- Dependencies: 2046
-- Name: binsartists_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE binsartists_id_seq OWNED BY binsartists.id;


--
-- TOC entry 2047 (class 1259 OID 21007)
-- Dependencies: 1915 6
-- Name: binsaudio_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE binsaudio_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.binsaudio_id_seq OWNER TO postgres;

--
-- TOC entry 3100 (class 0 OID 0)
-- Dependencies: 2047
-- Name: binsaudio_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE binsaudio_id_seq OWNED BY binsaudio.id;


--
-- TOC entry 2048 (class 1259 OID 21009)
-- Dependencies: 1916 6
-- Name: binskeywords_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE binskeywords_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.binskeywords_id_seq OWNER TO postgres;

--
-- TOC entry 3102 (class 0 OID 0)
-- Dependencies: 2048
-- Name: binskeywords_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE binskeywords_id_seq OWNED BY binskeywords.id;


--
-- TOC entry 2049 (class 1259 OID 21011)
-- Dependencies: 1917 6
-- Name: binsschedule_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE binsschedule_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.binsschedule_id_seq OWNER TO postgres;

--
-- TOC entry 3104 (class 0 OID 0)
-- Dependencies: 2049
-- Name: binsschedule_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE binsschedule_id_seq OWNED BY binsschedule.id;


--
-- TOC entry 2050 (class 1259 OID 21013)
-- Dependencies: 1918 6
-- Name: cartproperties_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE cartproperties_id_seq
    START WITH 7
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.cartproperties_id_seq OWNER TO postgres;

--
-- TOC entry 3106 (class 0 OID 0)
-- Dependencies: 2050
-- Name: cartproperties_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE cartproperties_id_seq OWNED BY cartproperties.id;


--
-- TOC entry 2051 (class 1259 OID 21015)
-- Dependencies: 1919 6
-- Name: cartsaudio_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE cartsaudio_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.cartsaudio_id_seq OWNER TO postgres;

--
-- TOC entry 3108 (class 0 OID 0)
-- Dependencies: 2051
-- Name: cartsaudio_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE cartsaudio_id_seq OWNED BY cartsaudio.id;


--
-- TOC entry 2052 (class 1259 OID 21017)
-- Dependencies: 1920 6
-- Name: cartsets_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE cartsets_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.cartsets_id_seq OWNER TO postgres;

--
-- TOC entry 3110 (class 0 OID 0)
-- Dependencies: 2052
-- Name: cartsets_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE cartsets_id_seq OWNED BY cartsets.id;


--
-- TOC entry 2053 (class 1259 OID 21019)
-- Dependencies: 1921 6
-- Name: cartsetsdir_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE cartsetsdir_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.cartsetsdir_id_seq OWNER TO postgres;

--
-- TOC entry 3112 (class 0 OID 0)
-- Dependencies: 2053
-- Name: cartsetsdir_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE cartsetsdir_id_seq OWNED BY cartsetsdir.id;


--
-- TOC entry 2054 (class 1259 OID 21021)
-- Dependencies: 6 1922
-- Name: cartsetsgroups_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE cartsetsgroups_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.cartsetsgroups_id_seq OWNER TO postgres;

--
-- TOC entry 3114 (class 0 OID 0)
-- Dependencies: 2054
-- Name: cartsetsgroups_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE cartsetsgroups_id_seq OWNED BY cartsetsgroups.id;


--
-- TOC entry 2055 (class 1259 OID 21023)
-- Dependencies: 1923 6
-- Name: cartsetsusers_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE cartsetsusers_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.cartsetsusers_id_seq OWNER TO postgres;

--
-- TOC entry 3116 (class 0 OID 0)
-- Dependencies: 2055
-- Name: cartsetsusers_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE cartsetsusers_id_seq OWNED BY cartsetsusers.id;


--
-- TOC entry 2056 (class 1259 OID 21025)
-- Dependencies: 1924 6
-- Name: cartstyleprops_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE cartstyleprops_id_seq
    START WITH 9
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.cartstyleprops_id_seq OWNER TO postgres;

--
-- TOC entry 3118 (class 0 OID 0)
-- Dependencies: 2056
-- Name: cartstyleprops_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE cartstyleprops_id_seq OWNED BY cartstyleprops.id;


--
-- TOC entry 2057 (class 1259 OID 21027)
-- Dependencies: 6 1925
-- Name: cartstyles_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE cartstyles_id_seq
    START WITH 5
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.cartstyles_id_seq OWNER TO postgres;

--
-- TOC entry 3120 (class 0 OID 0)
-- Dependencies: 2057
-- Name: cartstyles_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE cartstyles_id_seq OWNED BY cartstyles.id;


--
-- TOC entry 2058 (class 1259 OID 21029)
-- Dependencies: 6 1926
-- Name: cartwalls_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE cartwalls_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.cartwalls_id_seq OWNER TO postgres;

--
-- TOC entry 3122 (class 0 OID 0)
-- Dependencies: 2058
-- Name: cartwalls_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE cartwalls_id_seq OWNED BY cartwalls.id;


--
-- TOC entry 2059 (class 1259 OID 21031)
-- Dependencies: 6 1927
-- Name: changelog_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE changelog_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.changelog_id_seq OWNER TO postgres;

--
-- TOC entry 3124 (class 0 OID 0)
-- Dependencies: 2059
-- Name: changelog_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE changelog_id_seq OWNED BY changelog.id;


--
-- TOC entry 2060 (class 1259 OID 21033)
-- Dependencies: 1928 6
-- Name: cmscontent_contentid_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE cmscontent_contentid_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.cmscontent_contentid_seq OWNER TO postgres;

--
-- TOC entry 3126 (class 0 OID 0)
-- Dependencies: 2060
-- Name: cmscontent_contentid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE cmscontent_contentid_seq OWNED BY cmscontent.contentid;


--
-- TOC entry 2061 (class 1259 OID 21035)
-- Dependencies: 6 1929
-- Name: cmsregions_regionid_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE cmsregions_regionid_seq
    START WITH 9
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.cmsregions_regionid_seq OWNER TO postgres;

--
-- TOC entry 3128 (class 0 OID 0)
-- Dependencies: 2061
-- Name: cmsregions_regionid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE cmsregions_regionid_seq OWNED BY cmsregions.regionid;


--
-- TOC entry 2062 (class 1259 OID 21037)
-- Dependencies: 1930 6
-- Name: companies_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE companies_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.companies_id_seq OWNER TO postgres;

--
-- TOC entry 3130 (class 0 OID 0)
-- Dependencies: 2062
-- Name: companies_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE companies_id_seq OWNED BY companies.id;


--
-- TOC entry 2063 (class 1259 OID 21039)
-- Dependencies: 1931 6
-- Name: configs_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE configs_id_seq
    START WITH 4
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.configs_id_seq OWNER TO postgres;

--
-- TOC entry 3132 (class 0 OID 0)
-- Dependencies: 2063
-- Name: configs_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE configs_id_seq OWNED BY configs.id;


--
-- TOC entry 2064 (class 1259 OID 21041)
-- Dependencies: 1932 6
-- Name: configuration_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE configuration_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.configuration_id_seq OWNER TO postgres;

--
-- TOC entry 3134 (class 0 OID 0)
-- Dependencies: 2064
-- Name: configuration_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE configuration_id_seq OWNED BY configuration.id;


--
-- TOC entry 2065 (class 1259 OID 21043)
-- Dependencies: 6 1933
-- Name: dir_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE dir_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.dir_id_seq OWNER TO postgres;

--
-- TOC entry 3136 (class 0 OID 0)
-- Dependencies: 2065
-- Name: dir_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE dir_id_seq OWNED BY dir.id;


--
-- TOC entry 2066 (class 1259 OID 21045)
-- Dependencies: 6 1934
-- Name: dirgroups_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE dirgroups_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.dirgroups_id_seq OWNER TO postgres;

--
-- TOC entry 3138 (class 0 OID 0)
-- Dependencies: 2066
-- Name: dirgroups_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE dirgroups_id_seq OWNED BY dirgroups.id;


--
-- TOC entry 2067 (class 1259 OID 21047)
-- Dependencies: 6 1935
-- Name: dirusers_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE dirusers_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.dirusers_id_seq OWNER TO postgres;

--
-- TOC entry 3140 (class 0 OID 0)
-- Dependencies: 2067
-- Name: dirusers_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE dirusers_id_seq OWNED BY dirusers.id;


--
-- TOC entry 2068 (class 1259 OID 21049)
-- Dependencies: 1936 6
-- Name: email_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE email_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.email_id_seq OWNER TO postgres;

--
-- TOC entry 3142 (class 0 OID 0)
-- Dependencies: 2068
-- Name: email_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE email_id_seq OWNED BY email.id;


--
-- TOC entry 2069 (class 1259 OID 21051)
-- Dependencies: 6 1937
-- Name: extfeeds_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE extfeeds_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.extfeeds_id_seq OWNER TO postgres;

--
-- TOC entry 3144 (class 0 OID 0)
-- Dependencies: 2069
-- Name: extfeeds_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE extfeeds_id_seq OWNED BY extfeeds.id;


--
-- TOC entry 2070 (class 1259 OID 21053)
-- Dependencies: 1938 6
-- Name: fieldvalidators_ruleid_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE fieldvalidators_ruleid_seq
    START WITH 50
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.fieldvalidators_ruleid_seq OWNER TO postgres;

--
-- TOC entry 3146 (class 0 OID 0)
-- Dependencies: 2070
-- Name: fieldvalidators_ruleid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE fieldvalidators_ruleid_seq OWNED BY fieldvalidators.ruleid;


--
-- TOC entry 2071 (class 1259 OID 21055)
-- Dependencies: 1939 6
-- Name: formfields_fieldid_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE formfields_fieldid_seq
    START WITH 86
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.formfields_fieldid_seq OWNER TO postgres;

--
-- TOC entry 3148 (class 0 OID 0)
-- Dependencies: 2071
-- Name: formfields_fieldid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE formfields_fieldid_seq OWNED BY formfields.fieldid;


--
-- TOC entry 2072 (class 1259 OID 21057)
-- Dependencies: 1940 6
-- Name: forms_formid_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE forms_formid_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.forms_formid_seq OWNER TO postgres;

--
-- TOC entry 3150 (class 0 OID 0)
-- Dependencies: 2072
-- Name: forms_formid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE forms_formid_seq OWNED BY forms.formid;


--
-- TOC entry 2073 (class 1259 OID 21059)
-- Dependencies: 1941 6
-- Name: groups_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE groups_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.groups_id_seq OWNER TO postgres;

--
-- TOC entry 3152 (class 0 OID 0)
-- Dependencies: 2073
-- Name: groups_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE groups_id_seq OWNED BY groups.id;


--
-- TOC entry 2074 (class 1259 OID 21061)
-- Dependencies: 1942 6
-- Name: jinglepkgs_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE jinglepkgs_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.jinglepkgs_id_seq OWNER TO postgres;

--
-- TOC entry 3154 (class 0 OID 0)
-- Dependencies: 2074
-- Name: jinglepkgs_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE jinglepkgs_id_seq OWNED BY jinglepkgs.id;


--
-- TOC entry 2075 (class 1259 OID 21063)
-- Dependencies: 6 1943
-- Name: jingletypes_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE jingletypes_id_seq
    START WITH 7
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.jingletypes_id_seq OWNER TO postgres;

--
-- TOC entry 3156 (class 0 OID 0)
-- Dependencies: 2075
-- Name: jingletypes_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE jingletypes_id_seq OWNED BY jingletypes.id;


--
-- TOC entry 2076 (class 1259 OID 21065)
-- Dependencies: 1944 6
-- Name: keywords_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE keywords_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.keywords_id_seq OWNER TO postgres;

--
-- TOC entry 3158 (class 0 OID 0)
-- Dependencies: 2076
-- Name: keywords_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE keywords_id_seq OWNED BY keywords.id;


--
-- TOC entry 2077 (class 1259 OID 21067)
-- Dependencies: 6 1945
-- Name: lifespans_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE lifespans_id_seq
    START WITH 6
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.lifespans_id_seq OWNER TO postgres;

--
-- TOC entry 3160 (class 0 OID 0)
-- Dependencies: 2077
-- Name: lifespans_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE lifespans_id_seq OWNED BY lifespans.id;


--
-- TOC entry 2078 (class 1259 OID 21069)
-- Dependencies: 6 1946
-- Name: log_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE log_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.log_id_seq OWNER TO postgres;

--
-- TOC entry 3162 (class 0 OID 0)
-- Dependencies: 2078
-- Name: log_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE log_id_seq OWNED BY log.id;


--
-- TOC entry 2079 (class 1259 OID 21071)
-- Dependencies: 1947 6
-- Name: logentries_entryid_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE logentries_entryid_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.logentries_entryid_seq OWNER TO postgres;

--
-- TOC entry 3164 (class 0 OID 0)
-- Dependencies: 2079
-- Name: logentries_entryid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE logentries_entryid_seq OWNED BY logentries.entryid;


--
-- TOC entry 2080 (class 1259 OID 21073)
-- Dependencies: 6
-- Name: logentries_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE logentries_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.logentries_id_seq OWNER TO postgres;

--
-- TOC entry 2114 (class 1259 OID 22346)
-- Dependencies: 2115 6
-- Name: news_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE news_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.news_id_seq OWNER TO postgres;

--
-- TOC entry 3166 (class 0 OID 0)
-- Dependencies: 2114
-- Name: news_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE news_id_seq OWNED BY news.id;


--
-- TOC entry 2081 (class 1259 OID 21075)
-- Dependencies: 6 1948
-- Name: patches_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE patches_id_seq
    START WITH 3
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.patches_id_seq OWNER TO postgres;

--
-- TOC entry 3167 (class 0 OID 0)
-- Dependencies: 2081
-- Name: patches_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE patches_id_seq OWNED BY patches.id;


--
-- TOC entry 2082 (class 1259 OID 21077)
-- Dependencies: 6 1949
-- Name: playlists_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE playlists_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.playlists_id_seq OWNER TO postgres;

--
-- TOC entry 3169 (class 0 OID 0)
-- Dependencies: 2082
-- Name: playlists_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE playlists_id_seq OWNED BY playlists.id;


--
-- TOC entry 2083 (class 1259 OID 21079)
-- Dependencies: 6 1951
-- Name: realms_realmid_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE realms_realmid_seq
    START WITH 44
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.realms_realmid_seq OWNER TO postgres;

--
-- TOC entry 3171 (class 0 OID 0)
-- Dependencies: 2083
-- Name: realms_realmid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE realms_realmid_seq OWNED BY realms.realmid;


--
-- TOC entry 2084 (class 1259 OID 21081)
-- Dependencies: 6 1952
-- Name: realmuserlink_userid_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE realmuserlink_userid_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.realmuserlink_userid_seq OWNER TO postgres;

--
-- TOC entry 3173 (class 0 OID 0)
-- Dependencies: 2084
-- Name: realmuserlink_userid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE realmuserlink_userid_seq OWNED BY realmuserlink.userid;


--
-- TOC entry 2085 (class 1259 OID 21083)
-- Dependencies: 6 1953
-- Name: requests_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE requests_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.requests_id_seq OWNER TO postgres;

--
-- TOC entry 3175 (class 0 OID 0)
-- Dependencies: 2085
-- Name: requests_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE requests_id_seq OWNED BY requests.id;


--
-- TOC entry 2086 (class 1259 OID 21085)
-- Dependencies: 6 1954
-- Name: scripts_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE scripts_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.scripts_id_seq OWNER TO postgres;

--
-- TOC entry 3177 (class 0 OID 0)
-- Dependencies: 2086
-- Name: scripts_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE scripts_id_seq OWNED BY scripts.id;


--
-- TOC entry 2087 (class 1259 OID 21087)
-- Dependencies: 6 1955
-- Name: scriptsdir_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE scriptsdir_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.scriptsdir_id_seq OWNER TO postgres;

--
-- TOC entry 3179 (class 0 OID 0)
-- Dependencies: 2087
-- Name: scriptsdir_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE scriptsdir_id_seq OWNED BY scriptsdir.id;


--
-- TOC entry 2088 (class 1259 OID 21089)
-- Dependencies: 6 1956
-- Name: scriptsgroups_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE scriptsgroups_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.scriptsgroups_id_seq OWNER TO postgres;

--
-- TOC entry 3181 (class 0 OID 0)
-- Dependencies: 2088
-- Name: scriptsgroups_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE scriptsgroups_id_seq OWNED BY scriptsgroups.id;


--
-- TOC entry 2089 (class 1259 OID 21091)
-- Dependencies: 6 1957
-- Name: scriptsusers_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE scriptsusers_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.scriptsusers_id_seq OWNER TO postgres;

--
-- TOC entry 3183 (class 0 OID 0)
-- Dependencies: 2089
-- Name: scriptsusers_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE scriptsusers_id_seq OWNED BY scriptsusers.id;


--
-- TOC entry 2090 (class 1259 OID 21093)
-- Dependencies: 6
-- Name: sessions_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE sessions_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.sessions_id_seq OWNER TO postgres;

--
-- TOC entry 2091 (class 1259 OID 21095)
-- Dependencies: 6 1958
-- Name: sessions_sessionid_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE sessions_sessionid_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.sessions_sessionid_seq OWNER TO postgres;

--
-- TOC entry 3185 (class 0 OID 0)
-- Dependencies: 2091
-- Name: sessions_sessionid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE sessions_sessionid_seq OWNED BY sessions.sessionid;


--
-- TOC entry 2092 (class 1259 OID 21097)
-- Dependencies: 6
-- Name: sessionvalues_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE sessionvalues_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.sessionvalues_id_seq OWNER TO postgres;

--
-- TOC entry 2093 (class 1259 OID 21099)
-- Dependencies: 1959 6
-- Name: sessionvalues_valueid_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE sessionvalues_valueid_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.sessionvalues_valueid_seq OWNER TO postgres;

--
-- TOC entry 3187 (class 0 OID 0)
-- Dependencies: 2093
-- Name: sessionvalues_valueid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE sessionvalues_valueid_seq OWNED BY sessionvalues.valueid;


--
-- TOC entry 2094 (class 1259 OID 21101)
-- Dependencies: 6 1960
-- Name: showitems_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE showitems_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.showitems_id_seq OWNER TO postgres;

--
-- TOC entry 3189 (class 0 OID 0)
-- Dependencies: 2094
-- Name: showitems_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE showitems_id_seq OWNED BY showitems.id;


--
-- TOC entry 2095 (class 1259 OID 21103)
-- Dependencies: 6 1961
-- Name: showplandir_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE showplandir_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.showplandir_id_seq OWNER TO postgres;

--
-- TOC entry 3191 (class 0 OID 0)
-- Dependencies: 2095
-- Name: showplandir_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE showplandir_id_seq OWNED BY showplandir.id;


--
-- TOC entry 2096 (class 1259 OID 21105)
-- Dependencies: 6 1962
-- Name: showplangroups_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE showplangroups_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.showplangroups_id_seq OWNER TO postgres;

--
-- TOC entry 3193 (class 0 OID 0)
-- Dependencies: 2096
-- Name: showplangroups_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE showplangroups_id_seq OWNED BY showplangroups.id;


--
-- TOC entry 2097 (class 1259 OID 21107)
-- Dependencies: 6 1963
-- Name: showplans_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE showplans_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.showplans_id_seq OWNER TO postgres;

--
-- TOC entry 3195 (class 0 OID 0)
-- Dependencies: 2097
-- Name: showplans_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE showplans_id_seq OWNED BY showplans.id;


--
-- TOC entry 2098 (class 1259 OID 21109)
-- Dependencies: 1964 6
-- Name: showplansdir_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE showplansdir_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.showplansdir_id_seq OWNER TO postgres;

--
-- TOC entry 3197 (class 0 OID 0)
-- Dependencies: 2098
-- Name: showplansdir_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE showplansdir_id_seq OWNED BY showplansdir.id;


--
-- TOC entry 2099 (class 1259 OID 21111)
-- Dependencies: 1965 6
-- Name: showplansgroups_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE showplansgroups_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.showplansgroups_id_seq OWNER TO postgres;

--
-- TOC entry 3199 (class 0 OID 0)
-- Dependencies: 2099
-- Name: showplansgroups_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE showplansgroups_id_seq OWNED BY showplansgroups.id;


--
-- TOC entry 2100 (class 1259 OID 21113)
-- Dependencies: 6 1966
-- Name: showplansusers_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE showplansusers_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.showplansusers_id_seq OWNER TO postgres;

--
-- TOC entry 3201 (class 0 OID 0)
-- Dependencies: 2100
-- Name: showplansusers_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE showplansusers_id_seq OWNED BY showplansusers.id;


--
-- TOC entry 2101 (class 1259 OID 21115)
-- Dependencies: 6 1967
-- Name: showplanusers_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE showplanusers_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.showplanusers_id_seq OWNER TO postgres;

--
-- TOC entry 3203 (class 0 OID 0)
-- Dependencies: 2101
-- Name: showplanusers_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE showplanusers_id_seq OWNED BY showplanusers.id;


--
-- TOC entry 2102 (class 1259 OID 21117)
-- Dependencies: 1968 6
-- Name: sustschedule_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE sustschedule_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.sustschedule_id_seq OWNER TO postgres;

--
-- TOC entry 3205 (class 0 OID 0)
-- Dependencies: 2102
-- Name: sustschedule_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE sustschedule_id_seq OWNED BY sustschedule.id;


--
-- TOC entry 2103 (class 1259 OID 21119)
-- Dependencies: 1969 6
-- Name: tasks_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE tasks_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.tasks_id_seq OWNER TO postgres;

--
-- TOC entry 3207 (class 0 OID 0)
-- Dependencies: 2103
-- Name: tasks_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE tasks_id_seq OWNED BY tasks.id;


--
-- TOC entry 2104 (class 1259 OID 21121)
-- Dependencies: 1970 6
-- Name: taskschedule_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE taskschedule_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.taskschedule_id_seq OWNER TO postgres;

--
-- TOC entry 3209 (class 0 OID 0)
-- Dependencies: 2104
-- Name: taskschedule_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE taskschedule_id_seq OWNED BY taskschedule.id;


--
-- TOC entry 2105 (class 1259 OID 21123)
-- Dependencies: 1971 6
-- Name: templates_templateid_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE templates_templateid_seq
    START WITH 69
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.templates_templateid_seq OWNER TO postgres;

--
-- TOC entry 3211 (class 0 OID 0)
-- Dependencies: 2105
-- Name: templates_templateid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE templates_templateid_seq OWNED BY templates.templateid;


--
-- TOC entry 2106 (class 1259 OID 21125)
-- Dependencies: 6 1972
-- Name: txcategories_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE txcategories_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.txcategories_id_seq OWNER TO postgres;

--
-- TOC entry 3213 (class 0 OID 0)
-- Dependencies: 2106
-- Name: txcategories_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE txcategories_id_seq OWNED BY txcategories.id;


--
-- TOC entry 2107 (class 1259 OID 21127)
-- Dependencies: 1973 6
-- Name: txschedule_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE txschedule_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.txschedule_id_seq OWNER TO postgres;

--
-- TOC entry 3215 (class 0 OID 0)
-- Dependencies: 2107
-- Name: txschedule_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE txschedule_id_seq OWNED BY txschedule.id;


--
-- TOC entry 2108 (class 1259 OID 21129)
-- Dependencies: 6 1974
-- Name: txshows_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE txshows_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.txshows_id_seq OWNER TO postgres;

--
-- TOC entry 3217 (class 0 OID 0)
-- Dependencies: 2108
-- Name: txshows_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE txshows_id_seq OWNED BY txshows.id;


--
-- TOC entry 2109 (class 1259 OID 21131)
-- Dependencies: 6 1975
-- Name: txshowskeywords_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE txshowskeywords_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.txshowskeywords_id_seq OWNER TO postgres;

--
-- TOC entry 3219 (class 0 OID 0)
-- Dependencies: 2109
-- Name: txshowskeywords_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE txshowskeywords_id_seq OWNED BY txshowskeywords.id;


--
-- TOC entry 2110 (class 1259 OID 21133)
-- Dependencies: 6 1976
-- Name: txshowsusers_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE txshowsusers_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.txshowsusers_id_seq OWNER TO postgres;

--
-- TOC entry 3221 (class 0 OID 0)
-- Dependencies: 2110
-- Name: txshowsusers_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE txshowsusers_id_seq OWNED BY txshowsusers.id;


--
-- TOC entry 2111 (class 1259 OID 21135)
-- Dependencies: 1977 6
-- Name: users_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE users_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.users_id_seq OWNER TO postgres;

--
-- TOC entry 3223 (class 0 OID 0)
-- Dependencies: 2111
-- Name: users_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE users_id_seq OWNED BY users.id;


--
-- TOC entry 2112 (class 1259 OID 21137)
-- Dependencies: 6 1978
-- Name: usersconfigs_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE usersconfigs_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.usersconfigs_id_seq OWNER TO postgres;

--
-- TOC entry 3225 (class 0 OID 0)
-- Dependencies: 2112
-- Name: usersconfigs_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE usersconfigs_id_seq OWNED BY usersconfigs.id;


--
-- TOC entry 2113 (class 1259 OID 21139)
-- Dependencies: 6 1979
-- Name: usersgroups_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE usersgroups_id_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.usersgroups_id_seq OWNER TO postgres;

--
-- TOC entry 3227 (class 0 OID 0)
-- Dependencies: 2113
-- Name: usersgroups_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE usersgroups_id_seq OWNED BY usersgroups.id;


--
-- TOC entry 2445 (class 2604 OID 21141)
-- Dependencies: 2019 1887
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE advertschedule ALTER COLUMN id SET DEFAULT nextval('advertschedule_id_seq'::regclass);


--
-- TOC entry 2446 (class 2604 OID 21142)
-- Dependencies: 2020 1888
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE albums ALTER COLUMN id SET DEFAULT nextval('albums_id_seq'::regclass);


--
-- TOC entry 2447 (class 2604 OID 21143)
-- Dependencies: 2021 1889
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE archives ALTER COLUMN id SET DEFAULT nextval('archives_id_seq'::regclass);


--
-- TOC entry 2448 (class 2604 OID 21144)
-- Dependencies: 2022 1890
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE artists ALTER COLUMN id SET DEFAULT nextval('artists_id_seq'::regclass);


--
-- TOC entry 2449 (class 2604 OID 21145)
-- Dependencies: 2023 1891
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE artistskeywords ALTER COLUMN id SET DEFAULT nextval('artistskeywords_id_seq'::regclass);


--
-- TOC entry 2453 (class 2604 OID 21146)
-- Dependencies: 2024 1892
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE audio ALTER COLUMN id SET DEFAULT nextval('audio_id_seq'::regclass);


--
-- TOC entry 2454 (class 2604 OID 21147)
-- Dependencies: 2025 1893
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE audioartists ALTER COLUMN id SET DEFAULT nextval('audioartists_id_seq'::regclass);


--
-- TOC entry 2455 (class 2604 OID 21148)
-- Dependencies: 2026 1894
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE audiocomments ALTER COLUMN id SET DEFAULT nextval('audiocomments_id_seq'::regclass);


--
-- TOC entry 2458 (class 2604 OID 21149)
-- Dependencies: 2027 1895
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE audiodir ALTER COLUMN id SET DEFAULT nextval('audiodir_id_seq'::regclass);


--
-- TOC entry 2459 (class 2604 OID 21150)
-- Dependencies: 2028 1896
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE audioext ALTER COLUMN id SET DEFAULT nextval('audioext_id_seq'::regclass);


--
-- TOC entry 2460 (class 2604 OID 21151)
-- Dependencies: 2029 1897
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE audiogroups ALTER COLUMN id SET DEFAULT nextval('audiogroups_id_seq'::regclass);


--
-- TOC entry 2461 (class 2604 OID 21152)
-- Dependencies: 2030 1898
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE audiojinglepkgs ALTER COLUMN id SET DEFAULT nextval('audiojinglepkgs_id_seq'::regclass);


--
-- TOC entry 2462 (class 2604 OID 21153)
-- Dependencies: 2031 1899
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE audiokeywords ALTER COLUMN id SET DEFAULT nextval('audiokeywords_id_seq'::regclass);


--
-- TOC entry 2463 (class 2604 OID 21154)
-- Dependencies: 2032 1900
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE audiolog ALTER COLUMN id SET DEFAULT nextval('audiolog_id_seq'::regclass);


--
-- TOC entry 2464 (class 2604 OID 21155)
-- Dependencies: 2033 1901
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE audioplaylists ALTER COLUMN id SET DEFAULT nextval('audioplaylists_id_seq'::regclass);


--
-- TOC entry 2465 (class 2604 OID 21156)
-- Dependencies: 2034 1902
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE audiotypes ALTER COLUMN id SET DEFAULT nextval('audiotypes_id_seq'::regclass);


--
-- TOC entry 2466 (class 2604 OID 21157)
-- Dependencies: 2035 1903
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE audiousers ALTER COLUMN id SET DEFAULT nextval('audiousers_id_seq'::regclass);


--
-- TOC entry 2467 (class 2604 OID 21158)
-- Dependencies: 2036 1904
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE aw_items ALTER COLUMN id SET DEFAULT nextval('aw_items_id_seq'::regclass);


--
-- TOC entry 2468 (class 2604 OID 21159)
-- Dependencies: 2037 1905
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE aw_props ALTER COLUMN id SET DEFAULT nextval('aw_props_id_seq'::regclass);


--
-- TOC entry 2469 (class 2604 OID 21160)
-- Dependencies: 2040 1906
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE aw_sets ALTER COLUMN id SET DEFAULT nextval('aw_sets_id_seq'::regclass);


--
-- TOC entry 2472 (class 2604 OID 21161)
-- Dependencies: 2038 1907
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE aw_sets_dir ALTER COLUMN id SET DEFAULT nextval('aw_sets_dir_id_seq'::regclass);


--
-- TOC entry 2473 (class 2604 OID 21162)
-- Dependencies: 2039 1908
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE aw_sets_groups ALTER COLUMN id SET DEFAULT nextval('aw_sets_groups_id_seq'::regclass);


--
-- TOC entry 2474 (class 2604 OID 21163)
-- Dependencies: 2041 1909
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE aw_sets_users ALTER COLUMN id SET DEFAULT nextval('aw_sets_users_id_seq'::regclass);


--
-- TOC entry 2475 (class 2604 OID 21164)
-- Dependencies: 2042 1910
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE aw_styles ALTER COLUMN id SET DEFAULT nextval('aw_styles_id_seq'::regclass);


--
-- TOC entry 2476 (class 2604 OID 21165)
-- Dependencies: 2043 1911
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE aw_styles_props ALTER COLUMN id SET DEFAULT nextval('aw_styles_props_id_seq'::regclass);


--
-- TOC entry 2477 (class 2604 OID 21166)
-- Dependencies: 2044 1912
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE aw_walls ALTER COLUMN id SET DEFAULT nextval('aw_walls_id_seq'::regclass);


--
-- TOC entry 2478 (class 2604 OID 21167)
-- Dependencies: 2045 1913
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE bins ALTER COLUMN id SET DEFAULT nextval('bins_id_seq'::regclass);


--
-- TOC entry 2479 (class 2604 OID 21168)
-- Dependencies: 2046 1914
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE binsartists ALTER COLUMN id SET DEFAULT nextval('binsartists_id_seq'::regclass);


--
-- TOC entry 2480 (class 2604 OID 21169)
-- Dependencies: 2047 1915
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE binsaudio ALTER COLUMN id SET DEFAULT nextval('binsaudio_id_seq'::regclass);


--
-- TOC entry 2481 (class 2604 OID 21170)
-- Dependencies: 2048 1916
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE binskeywords ALTER COLUMN id SET DEFAULT nextval('binskeywords_id_seq'::regclass);


--
-- TOC entry 2482 (class 2604 OID 21171)
-- Dependencies: 2049 1917
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE binsschedule ALTER COLUMN id SET DEFAULT nextval('binsschedule_id_seq'::regclass);


--
-- TOC entry 2483 (class 2604 OID 21172)
-- Dependencies: 2050 1918
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE cartproperties ALTER COLUMN id SET DEFAULT nextval('cartproperties_id_seq'::regclass);


--
-- TOC entry 2484 (class 2604 OID 21173)
-- Dependencies: 2051 1919
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE cartsaudio ALTER COLUMN id SET DEFAULT nextval('cartsaudio_id_seq'::regclass);


--
-- TOC entry 2485 (class 2604 OID 21174)
-- Dependencies: 2052 1920
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE cartsets ALTER COLUMN id SET DEFAULT nextval('cartsets_id_seq'::regclass);


--
-- TOC entry 2488 (class 2604 OID 21175)
-- Dependencies: 2053 1921
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE cartsetsdir ALTER COLUMN id SET DEFAULT nextval('cartsetsdir_id_seq'::regclass);


--
-- TOC entry 2489 (class 2604 OID 21176)
-- Dependencies: 2054 1922
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE cartsetsgroups ALTER COLUMN id SET DEFAULT nextval('cartsetsgroups_id_seq'::regclass);


--
-- TOC entry 2490 (class 2604 OID 21177)
-- Dependencies: 2055 1923
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE cartsetsusers ALTER COLUMN id SET DEFAULT nextval('cartsetsusers_id_seq'::regclass);


--
-- TOC entry 2491 (class 2604 OID 21178)
-- Dependencies: 2056 1924
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE cartstyleprops ALTER COLUMN id SET DEFAULT nextval('cartstyleprops_id_seq'::regclass);


--
-- TOC entry 2492 (class 2604 OID 21179)
-- Dependencies: 2057 1925
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE cartstyles ALTER COLUMN id SET DEFAULT nextval('cartstyles_id_seq'::regclass);


--
-- TOC entry 2493 (class 2604 OID 21180)
-- Dependencies: 2058 1926
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE cartwalls ALTER COLUMN id SET DEFAULT nextval('cartwalls_id_seq'::regclass);


--
-- TOC entry 2494 (class 2604 OID 21181)
-- Dependencies: 2059 1927
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE changelog ALTER COLUMN id SET DEFAULT nextval('changelog_id_seq'::regclass);


--
-- TOC entry 2498 (class 2604 OID 21182)
-- Dependencies: 2060 1928
-- Name: contentid; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE cmscontent ALTER COLUMN contentid SET DEFAULT nextval('cmscontent_contentid_seq'::regclass);


--
-- TOC entry 2502 (class 2604 OID 21183)
-- Dependencies: 2061 1929
-- Name: regionid; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE cmsregions ALTER COLUMN regionid SET DEFAULT nextval('cmsregions_regionid_seq'::regclass);


--
-- TOC entry 2503 (class 2604 OID 21184)
-- Dependencies: 2062 1930
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE companies ALTER COLUMN id SET DEFAULT nextval('companies_id_seq'::regclass);


--
-- TOC entry 2504 (class 2604 OID 21185)
-- Dependencies: 2063 1931
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE configs ALTER COLUMN id SET DEFAULT nextval('configs_id_seq'::regclass);


--
-- TOC entry 2505 (class 2604 OID 21186)
-- Dependencies: 2064 1932
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE configuration ALTER COLUMN id SET DEFAULT nextval('configuration_id_seq'::regclass);


--
-- TOC entry 2506 (class 2604 OID 21187)
-- Dependencies: 2065 1933
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE dir ALTER COLUMN id SET DEFAULT nextval('dir_id_seq'::regclass);


--
-- TOC entry 2508 (class 2604 OID 21188)
-- Dependencies: 2066 1934
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE dirgroups ALTER COLUMN id SET DEFAULT nextval('dirgroups_id_seq'::regclass);


--
-- TOC entry 2509 (class 2604 OID 21189)
-- Dependencies: 2067 1935
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE dirusers ALTER COLUMN id SET DEFAULT nextval('dirusers_id_seq'::regclass);


--
-- TOC entry 2510 (class 2604 OID 21190)
-- Dependencies: 2068 1936
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE email ALTER COLUMN id SET DEFAULT nextval('email_id_seq'::regclass);


--
-- TOC entry 2511 (class 2604 OID 21191)
-- Dependencies: 2069 1937
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE extfeeds ALTER COLUMN id SET DEFAULT nextval('extfeeds_id_seq'::regclass);


--
-- TOC entry 2512 (class 2604 OID 21192)
-- Dependencies: 2070 1938
-- Name: ruleid; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE fieldvalidators ALTER COLUMN ruleid SET DEFAULT nextval('fieldvalidators_ruleid_seq'::regclass);


--
-- TOC entry 2519 (class 2604 OID 21193)
-- Dependencies: 2071 1939
-- Name: fieldid; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE formfields ALTER COLUMN fieldid SET DEFAULT nextval('formfields_fieldid_seq'::regclass);


--
-- TOC entry 2524 (class 2604 OID 21194)
-- Dependencies: 2072 1940
-- Name: formid; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE forms ALTER COLUMN formid SET DEFAULT nextval('forms_formid_seq'::regclass);


--
-- TOC entry 2525 (class 2604 OID 21195)
-- Dependencies: 2073 1941
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE groups ALTER COLUMN id SET DEFAULT nextval('groups_id_seq'::regclass);


--
-- TOC entry 2526 (class 2604 OID 21196)
-- Dependencies: 2074 1942
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE jinglepkgs ALTER COLUMN id SET DEFAULT nextval('jinglepkgs_id_seq'::regclass);


--
-- TOC entry 2527 (class 2604 OID 21197)
-- Dependencies: 2075 1943
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE jingletypes ALTER COLUMN id SET DEFAULT nextval('jingletypes_id_seq'::regclass);


--
-- TOC entry 2528 (class 2604 OID 21198)
-- Dependencies: 2076 1944
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE keywords ALTER COLUMN id SET DEFAULT nextval('keywords_id_seq'::regclass);


--
-- TOC entry 2529 (class 2604 OID 21199)
-- Dependencies: 2077 1945
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE lifespans ALTER COLUMN id SET DEFAULT nextval('lifespans_id_seq'::regclass);


--
-- TOC entry 2530 (class 2604 OID 21200)
-- Dependencies: 2078 1946
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE log ALTER COLUMN id SET DEFAULT nextval('log_id_seq'::regclass);


--
-- TOC entry 2531 (class 2604 OID 21201)
-- Dependencies: 2079 1947
-- Name: entryid; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE logentries ALTER COLUMN entryid SET DEFAULT nextval('logentries_entryid_seq'::regclass);


--
-- TOC entry 2584 (class 2604 OID 22351)
-- Dependencies: 2115 2114 2115
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE news ALTER COLUMN id SET DEFAULT nextval('news_id_seq'::regclass);


--
-- TOC entry 2534 (class 2604 OID 21202)
-- Dependencies: 2081 1948
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE patches ALTER COLUMN id SET DEFAULT nextval('patches_id_seq'::regclass);


--
-- TOC entry 2535 (class 2604 OID 21203)
-- Dependencies: 2082 1949
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE playlists ALTER COLUMN id SET DEFAULT nextval('playlists_id_seq'::regclass);


--
-- TOC entry 2536 (class 2604 OID 21204)
-- Dependencies: 2083 1951
-- Name: realmid; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE realms ALTER COLUMN realmid SET DEFAULT nextval('realms_realmid_seq'::regclass);


--
-- TOC entry 2538 (class 2604 OID 21205)
-- Dependencies: 2084 1952
-- Name: userid; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE realmuserlink ALTER COLUMN userid SET DEFAULT nextval('realmuserlink_userid_seq'::regclass);


--
-- TOC entry 2539 (class 2604 OID 21206)
-- Dependencies: 2085 1953
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE requests ALTER COLUMN id SET DEFAULT nextval('requests_id_seq'::regclass);


--
-- TOC entry 2540 (class 2604 OID 21207)
-- Dependencies: 2086 1954
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE scripts ALTER COLUMN id SET DEFAULT nextval('scripts_id_seq'::regclass);


--
-- TOC entry 2541 (class 2604 OID 21208)
-- Dependencies: 2087 1955
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE scriptsdir ALTER COLUMN id SET DEFAULT nextval('scriptsdir_id_seq'::regclass);


--
-- TOC entry 2544 (class 2604 OID 21209)
-- Dependencies: 2088 1956
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE scriptsgroups ALTER COLUMN id SET DEFAULT nextval('scriptsgroups_id_seq'::regclass);


--
-- TOC entry 2545 (class 2604 OID 21210)
-- Dependencies: 2089 1957
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE scriptsusers ALTER COLUMN id SET DEFAULT nextval('scriptsusers_id_seq'::regclass);


--
-- TOC entry 2550 (class 2604 OID 21211)
-- Dependencies: 2091 1958
-- Name: sessionid; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE sessions ALTER COLUMN sessionid SET DEFAULT nextval('sessions_sessionid_seq'::regclass);


--
-- TOC entry 2551 (class 2604 OID 21212)
-- Dependencies: 2093 1959
-- Name: valueid; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE sessionvalues ALTER COLUMN valueid SET DEFAULT nextval('sessionvalues_valueid_seq'::regclass);


--
-- TOC entry 2554 (class 2604 OID 21213)
-- Dependencies: 2094 1960
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE showitems ALTER COLUMN id SET DEFAULT nextval('showitems_id_seq'::regclass);


--
-- TOC entry 2555 (class 2604 OID 21214)
-- Dependencies: 2095 1961
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE showplandir ALTER COLUMN id SET DEFAULT nextval('showplandir_id_seq'::regclass);


--
-- TOC entry 2558 (class 2604 OID 21215)
-- Dependencies: 2096 1962
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE showplangroups ALTER COLUMN id SET DEFAULT nextval('showplangroups_id_seq'::regclass);


--
-- TOC entry 2559 (class 2604 OID 21216)
-- Dependencies: 2097 1963
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE showplans ALTER COLUMN id SET DEFAULT nextval('showplans_id_seq'::regclass);


--
-- TOC entry 2560 (class 2604 OID 21217)
-- Dependencies: 2098 1964
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE showplansdir ALTER COLUMN id SET DEFAULT nextval('showplansdir_id_seq'::regclass);


--
-- TOC entry 2563 (class 2604 OID 21218)
-- Dependencies: 2099 1965
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE showplansgroups ALTER COLUMN id SET DEFAULT nextval('showplansgroups_id_seq'::regclass);


--
-- TOC entry 2564 (class 2604 OID 21219)
-- Dependencies: 2100 1966
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE showplansusers ALTER COLUMN id SET DEFAULT nextval('showplansusers_id_seq'::regclass);


--
-- TOC entry 2565 (class 2604 OID 21220)
-- Dependencies: 2101 1967
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE showplanusers ALTER COLUMN id SET DEFAULT nextval('showplanusers_id_seq'::regclass);


--
-- TOC entry 2566 (class 2604 OID 21221)
-- Dependencies: 2102 1968
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE sustschedule ALTER COLUMN id SET DEFAULT nextval('sustschedule_id_seq'::regclass);


--
-- TOC entry 2567 (class 2604 OID 21222)
-- Dependencies: 2103 1969
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE tasks ALTER COLUMN id SET DEFAULT nextval('tasks_id_seq'::regclass);


--
-- TOC entry 2568 (class 2604 OID 21223)
-- Dependencies: 2104 1970
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE taskschedule ALTER COLUMN id SET DEFAULT nextval('taskschedule_id_seq'::regclass);


--
-- TOC entry 2573 (class 2604 OID 21224)
-- Dependencies: 2105 1971
-- Name: templateid; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE templates ALTER COLUMN templateid SET DEFAULT nextval('templates_templateid_seq'::regclass);


--
-- TOC entry 2574 (class 2604 OID 21225)
-- Dependencies: 2106 1972
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE txcategories ALTER COLUMN id SET DEFAULT nextval('txcategories_id_seq'::regclass);


--
-- TOC entry 2575 (class 2604 OID 21226)
-- Dependencies: 2107 1973
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE txschedule ALTER COLUMN id SET DEFAULT nextval('txschedule_id_seq'::regclass);


--
-- TOC entry 2576 (class 2604 OID 21227)
-- Dependencies: 2108 1974
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE txshows ALTER COLUMN id SET DEFAULT nextval('txshows_id_seq'::regclass);


--
-- TOC entry 2577 (class 2604 OID 21228)
-- Dependencies: 2109 1975
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE txshowskeywords ALTER COLUMN id SET DEFAULT nextval('txshowskeywords_id_seq'::regclass);


--
-- TOC entry 2578 (class 2604 OID 21229)
-- Dependencies: 2110 1976
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE txshowsusers ALTER COLUMN id SET DEFAULT nextval('txshowsusers_id_seq'::regclass);


--
-- TOC entry 2579 (class 2604 OID 21230)
-- Dependencies: 2111 1977
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE users ALTER COLUMN id SET DEFAULT nextval('users_id_seq'::regclass);


--
-- TOC entry 2582 (class 2604 OID 21231)
-- Dependencies: 2112 1978
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE usersconfigs ALTER COLUMN id SET DEFAULT nextval('usersconfigs_id_seq'::regclass);


--
-- TOC entry 2583 (class 2604 OID 21232)
-- Dependencies: 2113 1979
-- Name: id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE usersgroups ALTER COLUMN id SET DEFAULT nextval('usersgroups_id_seq'::regclass);


--
-- TOC entry 2586 (class 2606 OID 21540)
-- Dependencies: 1887 1887
-- Name: pk_advertschedule; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY advertschedule
    ADD CONSTRAINT pk_advertschedule PRIMARY KEY (id);


--
-- TOC entry 2588 (class 2606 OID 21542)
-- Dependencies: 1888 1888
-- Name: pk_albums; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY albums
    ADD CONSTRAINT pk_albums PRIMARY KEY (id);


--
-- TOC entry 2590 (class 2606 OID 21544)
-- Dependencies: 1889 1889
-- Name: pk_archives; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY archives
    ADD CONSTRAINT pk_archives PRIMARY KEY (id);


--
-- TOC entry 2594 (class 2606 OID 21546)
-- Dependencies: 1890 1890
-- Name: pk_artists; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY artists
    ADD CONSTRAINT pk_artists PRIMARY KEY (id);


--
-- TOC entry 2596 (class 2606 OID 21548)
-- Dependencies: 1891 1891
-- Name: pk_artistskeywords; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY artistskeywords
    ADD CONSTRAINT pk_artistskeywords PRIMARY KEY (id);


--
-- TOC entry 2600 (class 2606 OID 21550)
-- Dependencies: 1892 1892
-- Name: pk_audio; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY audio
    ADD CONSTRAINT pk_audio PRIMARY KEY (id);


--
-- TOC entry 2602 (class 2606 OID 21552)
-- Dependencies: 1893 1893
-- Name: pk_audioartists; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY audioartists
    ADD CONSTRAINT pk_audioartists PRIMARY KEY (id);


--
-- TOC entry 2604 (class 2606 OID 21554)
-- Dependencies: 1894 1894
-- Name: pk_audiocomments; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY audiocomments
    ADD CONSTRAINT pk_audiocomments PRIMARY KEY (id);


--
-- TOC entry 2609 (class 2606 OID 21556)
-- Dependencies: 1895 1895
-- Name: pk_audiodir; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY audiodir
    ADD CONSTRAINT pk_audiodir PRIMARY KEY (id);


--
-- TOC entry 2611 (class 2606 OID 21558)
-- Dependencies: 1896 1896
-- Name: pk_audioext; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY audioext
    ADD CONSTRAINT pk_audioext PRIMARY KEY (id);


--
-- TOC entry 2613 (class 2606 OID 21560)
-- Dependencies: 1897 1897
-- Name: pk_audiogroups; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY audiogroups
    ADD CONSTRAINT pk_audiogroups PRIMARY KEY (id);


--
-- TOC entry 2615 (class 2606 OID 21562)
-- Dependencies: 1898 1898
-- Name: pk_audiojinglepkgs; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY audiojinglepkgs
    ADD CONSTRAINT pk_audiojinglepkgs PRIMARY KEY (id);


--
-- TOC entry 2617 (class 2606 OID 21564)
-- Dependencies: 1899 1899
-- Name: pk_audiokeywords; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY audiokeywords
    ADD CONSTRAINT pk_audiokeywords PRIMARY KEY (id);


--
-- TOC entry 2619 (class 2606 OID 21566)
-- Dependencies: 1900 1900
-- Name: pk_audiolog; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY audiolog
    ADD CONSTRAINT pk_audiolog PRIMARY KEY (id);


--
-- TOC entry 2621 (class 2606 OID 21568)
-- Dependencies: 1901 1901
-- Name: pk_audioplaylists; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY audioplaylists
    ADD CONSTRAINT pk_audioplaylists PRIMARY KEY (id);


--
-- TOC entry 2623 (class 2606 OID 21570)
-- Dependencies: 1902 1902
-- Name: pk_audiotypes; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY audiotypes
    ADD CONSTRAINT pk_audiotypes PRIMARY KEY (id);


--
-- TOC entry 2625 (class 2606 OID 21572)
-- Dependencies: 1903 1903
-- Name: pk_audiousers; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY audiousers
    ADD CONSTRAINT pk_audiousers PRIMARY KEY (id);


--
-- TOC entry 2627 (class 2606 OID 21574)
-- Dependencies: 1904 1904
-- Name: pk_aw_items; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY aw_items
    ADD CONSTRAINT pk_aw_items PRIMARY KEY (id);


--
-- TOC entry 2629 (class 2606 OID 21576)
-- Dependencies: 1905 1905
-- Name: pk_aw_props; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY aw_props
    ADD CONSTRAINT pk_aw_props PRIMARY KEY (id);


--
-- TOC entry 2631 (class 2606 OID 21578)
-- Dependencies: 1906 1906
-- Name: pk_aw_sets; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY aw_sets
    ADD CONSTRAINT pk_aw_sets PRIMARY KEY (id);


--
-- TOC entry 2634 (class 2606 OID 21580)
-- Dependencies: 1907 1907
-- Name: pk_aw_sets_dir; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY aw_sets_dir
    ADD CONSTRAINT pk_aw_sets_dir PRIMARY KEY (id);


--
-- TOC entry 2636 (class 2606 OID 21582)
-- Dependencies: 1908 1908
-- Name: pk_aw_sets_groups; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY aw_sets_groups
    ADD CONSTRAINT pk_aw_sets_groups PRIMARY KEY (id);


--
-- TOC entry 2638 (class 2606 OID 21584)
-- Dependencies: 1909 1909
-- Name: pk_aw_sets_users; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY aw_sets_users
    ADD CONSTRAINT pk_aw_sets_users PRIMARY KEY (id);


--
-- TOC entry 2640 (class 2606 OID 21586)
-- Dependencies: 1910 1910
-- Name: pk_aw_styles; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY aw_styles
    ADD CONSTRAINT pk_aw_styles PRIMARY KEY (id);


--
-- TOC entry 2642 (class 2606 OID 21588)
-- Dependencies: 1911 1911
-- Name: pk_aw_styles_props; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY aw_styles_props
    ADD CONSTRAINT pk_aw_styles_props PRIMARY KEY (id);


--
-- TOC entry 2644 (class 2606 OID 21590)
-- Dependencies: 1912 1912
-- Name: pk_aw_walls; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY aw_walls
    ADD CONSTRAINT pk_aw_walls PRIMARY KEY (id);


--
-- TOC entry 2646 (class 2606 OID 21592)
-- Dependencies: 1913 1913
-- Name: pk_bins; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY bins
    ADD CONSTRAINT pk_bins PRIMARY KEY (id);


--
-- TOC entry 2648 (class 2606 OID 21594)
-- Dependencies: 1914 1914
-- Name: pk_binsartists; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY binsartists
    ADD CONSTRAINT pk_binsartists PRIMARY KEY (id);


--
-- TOC entry 2650 (class 2606 OID 21596)
-- Dependencies: 1915 1915
-- Name: pk_binsaudio; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY binsaudio
    ADD CONSTRAINT pk_binsaudio PRIMARY KEY (id);


--
-- TOC entry 2652 (class 2606 OID 21598)
-- Dependencies: 1916 1916
-- Name: pk_binskeywords; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY binskeywords
    ADD CONSTRAINT pk_binskeywords PRIMARY KEY (id);


--
-- TOC entry 2654 (class 2606 OID 21600)
-- Dependencies: 1917 1917
-- Name: pk_binsschedule; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY binsschedule
    ADD CONSTRAINT pk_binsschedule PRIMARY KEY (id);


--
-- TOC entry 2656 (class 2606 OID 21602)
-- Dependencies: 1918 1918
-- Name: pk_cartproperties; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY cartproperties
    ADD CONSTRAINT pk_cartproperties PRIMARY KEY (id);


--
-- TOC entry 2658 (class 2606 OID 21604)
-- Dependencies: 1919 1919
-- Name: pk_cartsaudio; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY cartsaudio
    ADD CONSTRAINT pk_cartsaudio PRIMARY KEY (id);


--
-- TOC entry 2660 (class 2606 OID 21606)
-- Dependencies: 1920 1920
-- Name: pk_cartsets; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY cartsets
    ADD CONSTRAINT pk_cartsets PRIMARY KEY (id);


--
-- TOC entry 2663 (class 2606 OID 21608)
-- Dependencies: 1921 1921
-- Name: pk_cartsetsdir; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY cartsetsdir
    ADD CONSTRAINT pk_cartsetsdir PRIMARY KEY (id);


--
-- TOC entry 2665 (class 2606 OID 21610)
-- Dependencies: 1922 1922
-- Name: pk_cartsetsgroups; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY cartsetsgroups
    ADD CONSTRAINT pk_cartsetsgroups PRIMARY KEY (id);


--
-- TOC entry 2667 (class 2606 OID 21612)
-- Dependencies: 1923 1923
-- Name: pk_cartsetsusers; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY cartsetsusers
    ADD CONSTRAINT pk_cartsetsusers PRIMARY KEY (id);


--
-- TOC entry 2669 (class 2606 OID 21614)
-- Dependencies: 1924 1924
-- Name: pk_cartstyleprops; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY cartstyleprops
    ADD CONSTRAINT pk_cartstyleprops PRIMARY KEY (id);


--
-- TOC entry 2671 (class 2606 OID 21616)
-- Dependencies: 1925 1925
-- Name: pk_cartstyles; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY cartstyles
    ADD CONSTRAINT pk_cartstyles PRIMARY KEY (id);


--
-- TOC entry 2673 (class 2606 OID 21618)
-- Dependencies: 1926 1926
-- Name: pk_cartwalls; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY cartwalls
    ADD CONSTRAINT pk_cartwalls PRIMARY KEY (id);


--
-- TOC entry 2675 (class 2606 OID 21620)
-- Dependencies: 1927 1927
-- Name: pk_changelog; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY changelog
    ADD CONSTRAINT pk_changelog PRIMARY KEY (id);


--
-- TOC entry 2677 (class 2606 OID 21622)
-- Dependencies: 1928 1928
-- Name: pk_cmscontent; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY cmscontent
    ADD CONSTRAINT pk_cmscontent PRIMARY KEY (contentid);


--
-- TOC entry 2679 (class 2606 OID 21624)
-- Dependencies: 1929 1929
-- Name: pk_cmsregions; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY cmsregions
    ADD CONSTRAINT pk_cmsregions PRIMARY KEY (regionid);


--
-- TOC entry 2681 (class 2606 OID 21626)
-- Dependencies: 1930 1930
-- Name: pk_companies; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY companies
    ADD CONSTRAINT pk_companies PRIMARY KEY (id);


--
-- TOC entry 2683 (class 2606 OID 21628)
-- Dependencies: 1931 1931
-- Name: pk_configs; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY configs
    ADD CONSTRAINT pk_configs PRIMARY KEY (id);


--
-- TOC entry 2685 (class 2606 OID 21630)
-- Dependencies: 1932 1932
-- Name: pk_configuration; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY configuration
    ADD CONSTRAINT pk_configuration PRIMARY KEY (id);


--
-- TOC entry 2687 (class 2606 OID 21632)
-- Dependencies: 1933 1933
-- Name: pk_dir; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY dir
    ADD CONSTRAINT pk_dir PRIMARY KEY (id);


--
-- TOC entry 2689 (class 2606 OID 21634)
-- Dependencies: 1934 1934
-- Name: pk_dirgroups; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY dirgroups
    ADD CONSTRAINT pk_dirgroups PRIMARY KEY (id);


--
-- TOC entry 2691 (class 2606 OID 21636)
-- Dependencies: 1935 1935
-- Name: pk_dirusers; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY dirusers
    ADD CONSTRAINT pk_dirusers PRIMARY KEY (id);


--
-- TOC entry 2693 (class 2606 OID 21638)
-- Dependencies: 1936 1936
-- Name: pk_email; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY email
    ADD CONSTRAINT pk_email PRIMARY KEY (id);


--
-- TOC entry 2695 (class 2606 OID 21640)
-- Dependencies: 1937 1937
-- Name: pk_extfeeds; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY extfeeds
    ADD CONSTRAINT pk_extfeeds PRIMARY KEY (id);


--
-- TOC entry 2697 (class 2606 OID 21642)
-- Dependencies: 1938 1938
-- Name: pk_fieldvalidators; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY fieldvalidators
    ADD CONSTRAINT pk_fieldvalidators PRIMARY KEY (ruleid);


--
-- TOC entry 2699 (class 2606 OID 21644)
-- Dependencies: 1939 1939
-- Name: pk_formfields; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY formfields
    ADD CONSTRAINT pk_formfields PRIMARY KEY (fieldid);


--
-- TOC entry 2701 (class 2606 OID 21646)
-- Dependencies: 1940 1940
-- Name: pk_forms; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY forms
    ADD CONSTRAINT pk_forms PRIMARY KEY (formid);


--
-- TOC entry 2703 (class 2606 OID 21648)
-- Dependencies: 1941 1941
-- Name: pk_groups; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY groups
    ADD CONSTRAINT pk_groups PRIMARY KEY (id);


--
-- TOC entry 2705 (class 2606 OID 21650)
-- Dependencies: 1942 1942
-- Name: pk_jinglepkgs; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY jinglepkgs
    ADD CONSTRAINT pk_jinglepkgs PRIMARY KEY (id);


--
-- TOC entry 2707 (class 2606 OID 21652)
-- Dependencies: 1943 1943
-- Name: pk_jingletypes; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY jingletypes
    ADD CONSTRAINT pk_jingletypes PRIMARY KEY (id);


--
-- TOC entry 2709 (class 2606 OID 21654)
-- Dependencies: 1944 1944
-- Name: pk_keywords; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY keywords
    ADD CONSTRAINT pk_keywords PRIMARY KEY (id);


--
-- TOC entry 2711 (class 2606 OID 21656)
-- Dependencies: 1945 1945
-- Name: pk_lifespans; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY lifespans
    ADD CONSTRAINT pk_lifespans PRIMARY KEY (id);


--
-- TOC entry 2713 (class 2606 OID 21658)
-- Dependencies: 1946 1946
-- Name: pk_log; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY log
    ADD CONSTRAINT pk_log PRIMARY KEY (id);


--
-- TOC entry 2715 (class 2606 OID 21660)
-- Dependencies: 1947 1947
-- Name: pk_logentries; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY logentries
    ADD CONSTRAINT pk_logentries PRIMARY KEY (entryid);


--
-- TOC entry 2783 (class 2606 OID 22356)
-- Dependencies: 2115 2115
-- Name: pk_news; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY news
    ADD CONSTRAINT pk_news PRIMARY KEY (id);


--
-- TOC entry 2717 (class 2606 OID 21662)
-- Dependencies: 1948 1948
-- Name: pk_patches; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY patches
    ADD CONSTRAINT pk_patches PRIMARY KEY (id);


--
-- TOC entry 2719 (class 2606 OID 21664)
-- Dependencies: 1949 1949
-- Name: pk_playlists; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY playlists
    ADD CONSTRAINT pk_playlists PRIMARY KEY (id);


--
-- TOC entry 2721 (class 2606 OID 21666)
-- Dependencies: 1950 1950 1950
-- Name: pk_realmgrouplink; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY realmgrouplink
    ADD CONSTRAINT pk_realmgrouplink PRIMARY KEY (groupid, realmid);


--
-- TOC entry 2723 (class 2606 OID 21668)
-- Dependencies: 1951 1951
-- Name: pk_realms; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY realms
    ADD CONSTRAINT pk_realms PRIMARY KEY (realmid);


--
-- TOC entry 2725 (class 2606 OID 21670)
-- Dependencies: 1952 1952 1952
-- Name: pk_realmuserlink; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY realmuserlink
    ADD CONSTRAINT pk_realmuserlink PRIMARY KEY (userid, realmid);


--
-- TOC entry 2727 (class 2606 OID 21672)
-- Dependencies: 1953 1953
-- Name: pk_requests; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY requests
    ADD CONSTRAINT pk_requests PRIMARY KEY (id);


--
-- TOC entry 2729 (class 2606 OID 21674)
-- Dependencies: 1954 1954
-- Name: pk_scripts; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY scripts
    ADD CONSTRAINT pk_scripts PRIMARY KEY (id);


--
-- TOC entry 2732 (class 2606 OID 21676)
-- Dependencies: 1955 1955
-- Name: pk_scriptsdir; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY scriptsdir
    ADD CONSTRAINT pk_scriptsdir PRIMARY KEY (id);


--
-- TOC entry 2734 (class 2606 OID 21678)
-- Dependencies: 1956 1956
-- Name: pk_scriptsgroups; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY scriptsgroups
    ADD CONSTRAINT pk_scriptsgroups PRIMARY KEY (id);


--
-- TOC entry 2736 (class 2606 OID 21680)
-- Dependencies: 1957 1957
-- Name: pk_scriptsusers; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY scriptsusers
    ADD CONSTRAINT pk_scriptsusers PRIMARY KEY (id);


--
-- TOC entry 2738 (class 2606 OID 21682)
-- Dependencies: 1958 1958
-- Name: pk_sessions; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY sessions
    ADD CONSTRAINT pk_sessions PRIMARY KEY (sessionid);


--
-- TOC entry 2740 (class 2606 OID 21684)
-- Dependencies: 1959 1959
-- Name: pk_sessionvalues; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY sessionvalues
    ADD CONSTRAINT pk_sessionvalues PRIMARY KEY (valueid);


--
-- TOC entry 2742 (class 2606 OID 21686)
-- Dependencies: 1960 1960
-- Name: pk_showitems; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY showitems
    ADD CONSTRAINT pk_showitems PRIMARY KEY (id);


--
-- TOC entry 2744 (class 2606 OID 21688)
-- Dependencies: 1961 1961
-- Name: pk_showplandir; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY showplandir
    ADD CONSTRAINT pk_showplandir PRIMARY KEY (id);


--
-- TOC entry 2746 (class 2606 OID 21690)
-- Dependencies: 1962 1962
-- Name: pk_showplangroups; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY showplangroups
    ADD CONSTRAINT pk_showplangroups PRIMARY KEY (id);


--
-- TOC entry 2748 (class 2606 OID 21692)
-- Dependencies: 1963 1963
-- Name: pk_showplans; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY showplans
    ADD CONSTRAINT pk_showplans PRIMARY KEY (id);


--
-- TOC entry 2751 (class 2606 OID 21694)
-- Dependencies: 1964 1964
-- Name: pk_showplansdir; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY showplansdir
    ADD CONSTRAINT pk_showplansdir PRIMARY KEY (id);


--
-- TOC entry 2753 (class 2606 OID 21696)
-- Dependencies: 1965 1965
-- Name: pk_showplansgroups; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY showplansgroups
    ADD CONSTRAINT pk_showplansgroups PRIMARY KEY (id);


--
-- TOC entry 2755 (class 2606 OID 21698)
-- Dependencies: 1966 1966
-- Name: pk_showplansusers; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY showplansusers
    ADD CONSTRAINT pk_showplansusers PRIMARY KEY (id);


--
-- TOC entry 2757 (class 2606 OID 21700)
-- Dependencies: 1967 1967
-- Name: pk_showplanusers; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY showplanusers
    ADD CONSTRAINT pk_showplanusers PRIMARY KEY (id);


--
-- TOC entry 2759 (class 2606 OID 21702)
-- Dependencies: 1968 1968
-- Name: pk_sustschedule; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY sustschedule
    ADD CONSTRAINT pk_sustschedule PRIMARY KEY (id);


--
-- TOC entry 2761 (class 2606 OID 21704)
-- Dependencies: 1969 1969
-- Name: pk_tasks; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY tasks
    ADD CONSTRAINT pk_tasks PRIMARY KEY (id);


--
-- TOC entry 2763 (class 2606 OID 21706)
-- Dependencies: 1970 1970
-- Name: pk_taskschedule; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY taskschedule
    ADD CONSTRAINT pk_taskschedule PRIMARY KEY (id);


--
-- TOC entry 2765 (class 2606 OID 21708)
-- Dependencies: 1971 1971
-- Name: pk_templates; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY templates
    ADD CONSTRAINT pk_templates PRIMARY KEY (templateid);


--
-- TOC entry 2767 (class 2606 OID 21710)
-- Dependencies: 1972 1972
-- Name: pk_txcategories; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY txcategories
    ADD CONSTRAINT pk_txcategories PRIMARY KEY (id);


--
-- TOC entry 2769 (class 2606 OID 21712)
-- Dependencies: 1973 1973
-- Name: pk_txschedule; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY txschedule
    ADD CONSTRAINT pk_txschedule PRIMARY KEY (id);


--
-- TOC entry 2771 (class 2606 OID 21714)
-- Dependencies: 1974 1974
-- Name: pk_txshows; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY txshows
    ADD CONSTRAINT pk_txshows PRIMARY KEY (id);


--
-- TOC entry 2773 (class 2606 OID 21716)
-- Dependencies: 1975 1975
-- Name: pk_txshowskeywords; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY txshowskeywords
    ADD CONSTRAINT pk_txshowskeywords PRIMARY KEY (id);


--
-- TOC entry 2775 (class 2606 OID 21718)
-- Dependencies: 1976 1976
-- Name: pk_txshowsusers; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY txshowsusers
    ADD CONSTRAINT pk_txshowsusers PRIMARY KEY (id);


--
-- TOC entry 2777 (class 2606 OID 21720)
-- Dependencies: 1977 1977
-- Name: pk_users; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY users
    ADD CONSTRAINT pk_users PRIMARY KEY (id);


--
-- TOC entry 2779 (class 2606 OID 21722)
-- Dependencies: 1978 1978
-- Name: pk_usersconfigs; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY usersconfigs
    ADD CONSTRAINT pk_usersconfigs PRIMARY KEY (id);


--
-- TOC entry 2781 (class 2606 OID 21724)
-- Dependencies: 1979 1979
-- Name: pk_usersgroups; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY usersgroups
    ADD CONSTRAINT pk_usersgroups PRIMARY KEY (id);


--
-- TOC entry 2591 (class 1259 OID 21725)
-- Dependencies: 1890
-- Name: idx_artists_alt_name; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE INDEX idx_artists_alt_name ON artists USING btree (alt_name);


--
-- TOC entry 2592 (class 1259 OID 21726)
-- Dependencies: 1890
-- Name: idx_artists_name; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE UNIQUE INDEX idx_artists_name ON artists USING btree (name);


--
-- TOC entry 2597 (class 1259 OID 21727)
-- Dependencies: 1892
-- Name: idx_audio_md5; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE UNIQUE INDEX idx_audio_md5 ON audio USING btree (md5);


--
-- TOC entry 2598 (class 1259 OID 21728)
-- Dependencies: 1892
-- Name: idx_audio_title; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE INDEX idx_audio_title ON audio USING btree (title);


--
-- TOC entry 2605 (class 1259 OID 21729)
-- Dependencies: 1895
-- Name: idx_audiodir_audio; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE INDEX idx_audiodir_audio ON audiodir USING btree (audioid);


--
-- TOC entry 2606 (class 1259 OID 21730)
-- Dependencies: 1895
-- Name: idx_audiodir_dirid; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE INDEX idx_audiodir_dirid ON audiodir USING btree (dirid);


--
-- TOC entry 2607 (class 1259 OID 21731)
-- Dependencies: 1895 1895
-- Name: idx_audiodir_uniquelink; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE UNIQUE INDEX idx_audiodir_uniquelink ON audiodir USING btree (audioid, linktype);


--
-- TOC entry 2632 (class 1259 OID 21732)
-- Dependencies: 1907 1907
-- Name: idx_aw_sets_dir_uniquelink; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE UNIQUE INDEX idx_aw_sets_dir_uniquelink ON aw_sets_dir USING btree (set_id, linktype);


--
-- TOC entry 2661 (class 1259 OID 21733)
-- Dependencies: 1921 1921
-- Name: idx_cartsetsdir_uniquelink; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE UNIQUE INDEX idx_cartsetsdir_uniquelink ON cartsetsdir USING btree (cartsetid, linktype);


--
-- TOC entry 2730 (class 1259 OID 21734)
-- Dependencies: 1955 1955
-- Name: idx_scriptsdir_uniquelink; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE UNIQUE INDEX idx_scriptsdir_uniquelink ON scriptsdir USING btree (scriptid, linktype);


--
-- TOC entry 2749 (class 1259 OID 21735)
-- Dependencies: 1964 1964
-- Name: idx_showplans_uniquelink; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE UNIQUE INDEX idx_showplans_uniquelink ON showplansdir USING btree (showplanid, linktype);


--
-- TOC entry 2230 (class 2618 OID 21736)
-- Dependencies: 1901 1901
-- Name: r_audioplaylists_delete; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_audioplaylists_delete AS ON DELETE TO audioplaylists DO NOTIFY t_playlists;


--
-- TOC entry 2231 (class 2618 OID 21737)
-- Dependencies: 1901 1901
-- Name: r_audioplaylists_insert; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_audioplaylists_insert AS ON INSERT TO audioplaylists DO NOTIFY t_playlists;


--
-- TOC entry 2232 (class 2618 OID 21738)
-- Dependencies: 1901 1901
-- Name: r_audioplaylists_update; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_audioplaylists_update AS ON UPDATE TO audioplaylists DO NOTIFY t_playlists;


--
-- TOC entry 2233 (class 2618 OID 21739)
-- Dependencies: 1904 1904
-- Name: r_aw_items_delete; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_aw_items_delete AS ON DELETE TO aw_items DO NOTIFY t_audiowall;


--
-- TOC entry 2234 (class 2618 OID 21740)
-- Dependencies: 1904 1904
-- Name: r_aw_items_insert; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_aw_items_insert AS ON INSERT TO aw_items DO NOTIFY t_audiowall;


--
-- TOC entry 2235 (class 2618 OID 21741)
-- Dependencies: 1904 1904
-- Name: r_aw_items_update; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_aw_items_update AS ON UPDATE TO aw_items DO NOTIFY t_audiowall;


--
-- TOC entry 2236 (class 2618 OID 21742)
-- Dependencies: 1919 1919
-- Name: r_cartsaudio_delete; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_cartsaudio_delete AS ON DELETE TO cartsaudio DO NOTIFY trig_id3;


--
-- TOC entry 2237 (class 2618 OID 21743)
-- Dependencies: 1919 1919
-- Name: r_cartsaudio_insert; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_cartsaudio_insert AS ON INSERT TO cartsaudio DO NOTIFY trig_id3;


--
-- TOC entry 2238 (class 2618 OID 21744)
-- Dependencies: 1919 1919
-- Name: r_cartsaudio_update; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_cartsaudio_update AS ON UPDATE TO cartsaudio DO NOTIFY trig_id3;


--
-- TOC entry 2239 (class 2618 OID 21745)
-- Dependencies: 1932 1932
-- Name: r_configuration_insert; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_configuration_insert AS ON INSERT TO configuration DO NOTIFY t_configuration;


--
-- TOC entry 2240 (class 2618 OID 21746)
-- Dependencies: 1932 1932
-- Name: r_configuration_update; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_configuration_update AS ON UPDATE TO configuration DO NOTIFY t_configuration;


--
-- TOC entry 2241 (class 2618 OID 21747)
-- Dependencies: 1936 1936
-- Name: r_email_delete; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_email_delete AS ON DELETE TO email DO NOTIFY t_email;


--
-- TOC entry 2242 (class 2618 OID 21748)
-- Dependencies: 1936 1936
-- Name: r_email_insert; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_email_insert AS ON INSERT TO email DO NOTIFY t_email;


--
-- TOC entry 2243 (class 2618 OID 21749)
-- Dependencies: 1936 1936
-- Name: r_email_update; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_email_update AS ON UPDATE TO email DO NOTIFY t_email;


--
-- TOC entry 2244 (class 2618 OID 21750)
-- Dependencies: 1946 1946
-- Name: r_log_delete; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_log_delete AS ON DELETE TO log DO NOTIFY t_log;


--
-- TOC entry 2245 (class 2618 OID 21751)
-- Dependencies: 1946 1946
-- Name: r_log_insert; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_log_insert AS ON INSERT TO log DO NOTIFY t_log;


--
-- TOC entry 2246 (class 2618 OID 21752)
-- Dependencies: 1946 1946
-- Name: r_log_update; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_log_update AS ON UPDATE TO log DO NOTIFY t_log;


--
-- TOC entry 2247 (class 2618 OID 21753)
-- Dependencies: 1949 1949
-- Name: r_playlists_delete; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_playlists_delete AS ON DELETE TO playlists DO NOTIFY t_playlists;


--
-- TOC entry 2248 (class 2618 OID 21754)
-- Dependencies: 1949 1949
-- Name: r_playlists_insert; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_playlists_insert AS ON INSERT TO playlists DO NOTIFY t_playlists;


--
-- TOC entry 2249 (class 2618 OID 21755)
-- Dependencies: 1949 1949
-- Name: r_playlists_update; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_playlists_update AS ON UPDATE TO playlists DO NOTIFY t_playlists;


--
-- TOC entry 2250 (class 2618 OID 21756)
-- Dependencies: 1973 1973
-- Name: r_txschedule_delete; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_txschedule_delete AS ON DELETE TO txschedule DO NOTIFY t_txschedule;


--
-- TOC entry 2251 (class 2618 OID 21757)
-- Dependencies: 1973 1973
-- Name: r_txschedule_insert; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_txschedule_insert AS ON INSERT TO txschedule DO NOTIFY t_txschedule;


--
-- TOC entry 2252 (class 2618 OID 21758)
-- Dependencies: 1973 1973
-- Name: r_txschedule_update; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_txschedule_update AS ON UPDATE TO txschedule DO NOTIFY t_txschedule;


--
-- TOC entry 2253 (class 2618 OID 21759)
-- Dependencies: 1974 1974
-- Name: r_txshowsusers_update; Type: RULE; Schema: public; Owner: postgres
--

CREATE RULE r_txshowsusers_update AS ON UPDATE TO txshows DO NOTIFY t_txschedule;


--
-- TOC entry 2897 (class 2620 OID 21760)
-- Dependencies: 1892 21
-- Name: t_audio_delete; Type: TRIGGER; Schema: public; Owner: postgres
--

CREATE TRIGGER t_audio_delete
    BEFORE DELETE ON audio
    FOR EACH ROW
    EXECUTE PROCEDURE f_audio_delete();


--
-- TOC entry 2898 (class 2620 OID 21761)
-- Dependencies: 22 1905
-- Name: t_aw_props_delete; Type: TRIGGER; Schema: public; Owner: postgres
--

CREATE TRIGGER t_aw_props_delete
    BEFORE DELETE ON aw_props
    FOR EACH ROW
    EXECUTE PROCEDURE f_aw_props_delete();


--
-- TOC entry 2899 (class 2620 OID 21762)
-- Dependencies: 23 1906
-- Name: t_aw_sets_delete; Type: TRIGGER; Schema: public; Owner: postgres
--

CREATE TRIGGER t_aw_sets_delete
    BEFORE DELETE ON aw_sets
    FOR EACH ROW
    EXECUTE PROCEDURE f_aw_sets_delete();


--
-- TOC entry 2900 (class 2620 OID 21763)
-- Dependencies: 24 1910
-- Name: t_aw_styles_delete; Type: TRIGGER; Schema: public; Owner: postgres
--

CREATE TRIGGER t_aw_styles_delete
    BEFORE DELETE ON aw_styles
    FOR EACH ROW
    EXECUTE PROCEDURE f_aw_styles_delete();


--
-- TOC entry 2901 (class 2620 OID 21764)
-- Dependencies: 25 1912
-- Name: t_aw_walls_delete; Type: TRIGGER; Schema: public; Owner: postgres
--

CREATE TRIGGER t_aw_walls_delete
    BEFORE DELETE ON aw_walls
    FOR EACH ROW
    EXECUTE PROCEDURE f_aw_walls_delete();


--
-- TOC entry 2902 (class 2620 OID 21765)
-- Dependencies: 26 1933
-- Name: t_dir_delete; Type: TRIGGER; Schema: public; Owner: postgres
--

CREATE TRIGGER t_dir_delete
    BEFORE DELETE ON dir
    FOR EACH ROW
    EXECUTE PROCEDURE f_dir_delete();


--
-- TOC entry 2903 (class 2620 OID 21766)
-- Dependencies: 27 1941
-- Name: t_groups_delete; Type: TRIGGER; Schema: public; Owner: postgres
--

CREATE TRIGGER t_groups_delete
    BEFORE DELETE ON groups
    FOR EACH ROW
    EXECUTE PROCEDURE f_groups_delete();


--
-- TOC entry 2904 (class 2620 OID 21767)
-- Dependencies: 1954 28
-- Name: t_scripts_delete; Type: TRIGGER; Schema: public; Owner: postgres
--

CREATE TRIGGER t_scripts_delete
    BEFORE DELETE ON scripts
    FOR EACH ROW
    EXECUTE PROCEDURE f_scripts_delete();


--
-- TOC entry 2905 (class 2620 OID 21768)
-- Dependencies: 1963 29
-- Name: t_showplans_delete; Type: TRIGGER; Schema: public; Owner: postgres
--

CREATE TRIGGER t_showplans_delete
    BEFORE DELETE ON showplans
    FOR EACH ROW
    EXECUTE PROCEDURE f_showplans_delete();


--
-- TOC entry 2906 (class 2620 OID 21769)
-- Dependencies: 1977 31
-- Name: t_users_delete; Type: TRIGGER; Schema: public; Owner: postgres
--

CREATE TRIGGER t_users_delete
    BEFORE DELETE ON users
    FOR EACH ROW
    EXECUTE PROCEDURE f_users_delete();


--
-- TOC entry 2850 (class 2606 OID 21770)
-- Dependencies: 2686 1935 1933
-- Name: dirusers_fk_dirid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY dirusers
    ADD CONSTRAINT dirusers_fk_dirid FOREIGN KEY (dirid) REFERENCES dir(id);


--
-- TOC entry 2784 (class 2606 OID 21775)
-- Dependencies: 1892 1887 2599
-- Name: fk_advertschedule_audioid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY advertschedule
    ADD CONSTRAINT fk_advertschedule_audioid FOREIGN KEY (audioid) REFERENCES audio(id);


--
-- TOC entry 2785 (class 2606 OID 21780)
-- Dependencies: 1891 1890 2593
-- Name: fk_artistskeywords_artistid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY artistskeywords
    ADD CONSTRAINT fk_artistskeywords_artistid FOREIGN KEY (artistid) REFERENCES artists(id);


--
-- TOC entry 2786 (class 2606 OID 21785)
-- Dependencies: 2708 1944 1891
-- Name: fk_artistskeywords_keywordid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY artistskeywords
    ADD CONSTRAINT fk_artistskeywords_keywordid FOREIGN KEY (keywordid) REFERENCES keywords(id);


--
-- TOC entry 2787 (class 2606 OID 21790)
-- Dependencies: 2680 1892 1930
-- Name: fk_audio_advert_company; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audio
    ADD CONSTRAINT fk_audio_advert_company FOREIGN KEY (advert_company) REFERENCES companies(id);


--
-- TOC entry 2788 (class 2606 OID 21795)
-- Dependencies: 2589 1892 1889
-- Name: fk_audio_archive; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audio
    ADD CONSTRAINT fk_audio_archive FOREIGN KEY (archive) REFERENCES archives(id);


--
-- TOC entry 2789 (class 2606 OID 21800)
-- Dependencies: 2776 1892 1977
-- Name: fk_audio_creator; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audio
    ADD CONSTRAINT fk_audio_creator FOREIGN KEY (creator) REFERENCES users(id);


--
-- TOC entry 2790 (class 2606 OID 21805)
-- Dependencies: 2710 1892 1945
-- Name: fk_audio_lifespan; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audio
    ADD CONSTRAINT fk_audio_lifespan FOREIGN KEY (lifespan) REFERENCES lifespans(id);


--
-- TOC entry 2791 (class 2606 OID 21810)
-- Dependencies: 2587 1892 1888
-- Name: fk_audio_music_album; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audio
    ADD CONSTRAINT fk_audio_music_album FOREIGN KEY (music_album) REFERENCES albums(id);


--
-- TOC entry 2792 (class 2606 OID 21815)
-- Dependencies: 2622 1892 1902
-- Name: fk_audio_type; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audio
    ADD CONSTRAINT fk_audio_type FOREIGN KEY (type) REFERENCES audiotypes(id);


--
-- TOC entry 2793 (class 2606 OID 21820)
-- Dependencies: 1893 1890 2593
-- Name: fk_audioartists_artistid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audioartists
    ADD CONSTRAINT fk_audioartists_artistid FOREIGN KEY (artistid) REFERENCES artists(id);


--
-- TOC entry 2794 (class 2606 OID 21825)
-- Dependencies: 1892 1893 2599
-- Name: fk_audioartists_audioid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audioartists
    ADD CONSTRAINT fk_audioartists_audioid FOREIGN KEY (audioid) REFERENCES audio(id);


--
-- TOC entry 2795 (class 2606 OID 21830)
-- Dependencies: 1892 1894 2599
-- Name: fk_audiocomments_audioid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audiocomments
    ADD CONSTRAINT fk_audiocomments_audioid FOREIGN KEY (audioid) REFERENCES audio(id);


--
-- TOC entry 2796 (class 2606 OID 21835)
-- Dependencies: 2776 1894 1977
-- Name: fk_audiocomments_userid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audiocomments
    ADD CONSTRAINT fk_audiocomments_userid FOREIGN KEY (userid) REFERENCES users(id);


--
-- TOC entry 2797 (class 2606 OID 21840)
-- Dependencies: 1892 1895 2599
-- Name: fk_audiodir_audioid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audiodir
    ADD CONSTRAINT fk_audiodir_audioid FOREIGN KEY (audioid) REFERENCES audio(id);


--
-- TOC entry 2798 (class 2606 OID 21845)
-- Dependencies: 1933 1895 2686
-- Name: fk_audiodir_dirid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audiodir
    ADD CONSTRAINT fk_audiodir_dirid FOREIGN KEY (dirid) REFERENCES dir(id);


--
-- TOC entry 2799 (class 2606 OID 21850)
-- Dependencies: 1892 1897 2599
-- Name: fk_audiogroups_audioid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audiogroups
    ADD CONSTRAINT fk_audiogroups_audioid FOREIGN KEY (audioid) REFERENCES audio(id);


--
-- TOC entry 2800 (class 2606 OID 21855)
-- Dependencies: 1941 1897 2702
-- Name: fk_audiogroups_groupid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audiogroups
    ADD CONSTRAINT fk_audiogroups_groupid FOREIGN KEY (groupid) REFERENCES groups(id);


--
-- TOC entry 2801 (class 2606 OID 21860)
-- Dependencies: 1892 1898 2599
-- Name: fk_audiojinglepkgs_audioid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audiojinglepkgs
    ADD CONSTRAINT fk_audiojinglepkgs_audioid FOREIGN KEY (audioid) REFERENCES audio(id);


--
-- TOC entry 2802 (class 2606 OID 21865)
-- Dependencies: 1942 1898 2704
-- Name: fk_audiojinglepkgs_jinglepkgid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audiojinglepkgs
    ADD CONSTRAINT fk_audiojinglepkgs_jinglepkgid FOREIGN KEY (jinglepkgid) REFERENCES jinglepkgs(id);


--
-- TOC entry 2803 (class 2606 OID 21870)
-- Dependencies: 1943 1898 2706
-- Name: fk_audiojinglepkgs_jingletypeid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audiojinglepkgs
    ADD CONSTRAINT fk_audiojinglepkgs_jingletypeid FOREIGN KEY (jingletypeid) REFERENCES jingletypes(id);


--
-- TOC entry 2804 (class 2606 OID 21875)
-- Dependencies: 1892 1899 2599
-- Name: fk_audiokeywords_audioid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audiokeywords
    ADD CONSTRAINT fk_audiokeywords_audioid FOREIGN KEY (audioid) REFERENCES audio(id);


--
-- TOC entry 2805 (class 2606 OID 21880)
-- Dependencies: 1944 1899 2708
-- Name: fk_audiokeywords_keywordid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audiokeywords
    ADD CONSTRAINT fk_audiokeywords_keywordid FOREIGN KEY (keywordid) REFERENCES keywords(id);


--
-- TOC entry 2806 (class 2606 OID 21885)
-- Dependencies: 1892 1900 2599
-- Name: fk_audiolog_audioid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audiolog
    ADD CONSTRAINT fk_audiolog_audioid FOREIGN KEY (audioid) REFERENCES audio(id);


--
-- TOC entry 2807 (class 2606 OID 21890)
-- Dependencies: 1977 1900 2776
-- Name: fk_audiolog_userid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audiolog
    ADD CONSTRAINT fk_audiolog_userid FOREIGN KEY (userid) REFERENCES users(id);


--
-- TOC entry 2808 (class 2606 OID 21895)
-- Dependencies: 2599 1901 1892
-- Name: fk_audioplaylists_audioid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audioplaylists
    ADD CONSTRAINT fk_audioplaylists_audioid FOREIGN KEY (audioid) REFERENCES audio(id);


--
-- TOC entry 2809 (class 2606 OID 21900)
-- Dependencies: 1901 1949 2718
-- Name: fk_audioplaylists_playlistid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audioplaylists
    ADD CONSTRAINT fk_audioplaylists_playlistid FOREIGN KEY (playlistid) REFERENCES playlists(id);


--
-- TOC entry 2810 (class 2606 OID 21905)
-- Dependencies: 2599 1903 1892
-- Name: fk_audiousers_audioid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audiousers
    ADD CONSTRAINT fk_audiousers_audioid FOREIGN KEY (audioid) REFERENCES audio(id);


--
-- TOC entry 2811 (class 2606 OID 21910)
-- Dependencies: 1977 1903 2776
-- Name: fk_audiousers_userid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY audiousers
    ADD CONSTRAINT fk_audiousers_userid FOREIGN KEY (userid) REFERENCES users(id);


--
-- TOC entry 2812 (class 2606 OID 21915)
-- Dependencies: 1892 1904 2599
-- Name: fk_aw_items_audio_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY aw_items
    ADD CONSTRAINT fk_aw_items_audio_id FOREIGN KEY (audio_id) REFERENCES audio(id);


--
-- TOC entry 2813 (class 2606 OID 21920)
-- Dependencies: 1910 1904 2639
-- Name: fk_aw_items_aw_styles_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY aw_items
    ADD CONSTRAINT fk_aw_items_aw_styles_id FOREIGN KEY (style_id) REFERENCES aw_styles(id);


--
-- TOC entry 2814 (class 2606 OID 21925)
-- Dependencies: 2643 1904 1912
-- Name: fk_aw_items_aw_walls_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY aw_items
    ADD CONSTRAINT fk_aw_items_aw_walls_id FOREIGN KEY (wall_id) REFERENCES aw_walls(id);


--
-- TOC entry 2815 (class 2606 OID 21930)
-- Dependencies: 1906 2630 1907
-- Name: fk_aw_sets_dir_aw_sets_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY aw_sets_dir
    ADD CONSTRAINT fk_aw_sets_dir_aw_sets_id FOREIGN KEY (set_id) REFERENCES aw_sets(id);


--
-- TOC entry 2816 (class 2606 OID 21935)
-- Dependencies: 1907 1933 2686
-- Name: fk_aw_sets_dir_dir_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY aw_sets_dir
    ADD CONSTRAINT fk_aw_sets_dir_dir_id FOREIGN KEY (dir_id) REFERENCES dir(id);


--
-- TOC entry 2817 (class 2606 OID 21940)
-- Dependencies: 2630 1906 1908
-- Name: fk_aw_sets_groups_aw_sets_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY aw_sets_groups
    ADD CONSTRAINT fk_aw_sets_groups_aw_sets_id FOREIGN KEY (set_id) REFERENCES aw_sets(id);


--
-- TOC entry 2818 (class 2606 OID 21945)
-- Dependencies: 2702 1941 1908
-- Name: fk_aw_sets_groups_groups_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY aw_sets_groups
    ADD CONSTRAINT fk_aw_sets_groups_groups_id FOREIGN KEY (group_id) REFERENCES groups(id);


--
-- TOC entry 2819 (class 2606 OID 21950)
-- Dependencies: 2630 1906 1909
-- Name: fk_aw_sets_users_aw_sets_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY aw_sets_users
    ADD CONSTRAINT fk_aw_sets_users_aw_sets_id FOREIGN KEY (set_id) REFERENCES aw_sets(id);


--
-- TOC entry 2820 (class 2606 OID 21955)
-- Dependencies: 2776 1977 1909
-- Name: fk_aw_sets_users_users_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY aw_sets_users
    ADD CONSTRAINT fk_aw_sets_users_users_id FOREIGN KEY (user_id) REFERENCES users(id);


--
-- TOC entry 2821 (class 2606 OID 21960)
-- Dependencies: 2628 1905 1911
-- Name: fk_aw_styles_props_aw_props_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY aw_styles_props
    ADD CONSTRAINT fk_aw_styles_props_aw_props_id FOREIGN KEY (prop_id) REFERENCES aw_props(id);


--
-- TOC entry 2822 (class 2606 OID 21965)
-- Dependencies: 1910 2639 1911
-- Name: fk_aw_styles_props_aw_styles_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY aw_styles_props
    ADD CONSTRAINT fk_aw_styles_props_aw_styles_id FOREIGN KEY (style_id) REFERENCES aw_styles(id);


--
-- TOC entry 2823 (class 2606 OID 21970)
-- Dependencies: 1906 1912 2630
-- Name: fk_aw_walls_aw_set_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY aw_walls
    ADD CONSTRAINT fk_aw_walls_aw_set_id FOREIGN KEY (set_id) REFERENCES aw_sets(id);


--
-- TOC entry 2824 (class 2606 OID 21975)
-- Dependencies: 1890 1914 2593
-- Name: fk_binsartists_artistid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY binsartists
    ADD CONSTRAINT fk_binsartists_artistid FOREIGN KEY (artistid) REFERENCES artists(id);


--
-- TOC entry 2825 (class 2606 OID 21980)
-- Dependencies: 2645 1914 1913
-- Name: fk_binsartists_binid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY binsartists
    ADD CONSTRAINT fk_binsartists_binid FOREIGN KEY (binid) REFERENCES bins(id);


--
-- TOC entry 2826 (class 2606 OID 21985)
-- Dependencies: 1892 1915 2599
-- Name: fk_binsaudio_audioid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY binsaudio
    ADD CONSTRAINT fk_binsaudio_audioid FOREIGN KEY (audioid) REFERENCES audio(id);


--
-- TOC entry 2827 (class 2606 OID 21990)
-- Dependencies: 1913 1915 2645
-- Name: fk_binsaudio_binid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY binsaudio
    ADD CONSTRAINT fk_binsaudio_binid FOREIGN KEY (binid) REFERENCES bins(id);


--
-- TOC entry 2828 (class 2606 OID 21995)
-- Dependencies: 1913 1916 2645
-- Name: fk_binskeywords_binid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY binskeywords
    ADD CONSTRAINT fk_binskeywords_binid FOREIGN KEY (binid) REFERENCES bins(id);


--
-- TOC entry 2829 (class 2606 OID 22000)
-- Dependencies: 1944 1916 2708
-- Name: fk_binskeywords_keywordid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY binskeywords
    ADD CONSTRAINT fk_binskeywords_keywordid FOREIGN KEY (keywordid) REFERENCES keywords(id);


--
-- TOC entry 2830 (class 2606 OID 22005)
-- Dependencies: 1913 1917 2645
-- Name: fk_binsschedule_binid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY binsschedule
    ADD CONSTRAINT fk_binsschedule_binid FOREIGN KEY (binid) REFERENCES bins(id);


--
-- TOC entry 2831 (class 2606 OID 22010)
-- Dependencies: 1892 2599 1919
-- Name: fk_cartsaudio_audioid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cartsaudio
    ADD CONSTRAINT fk_cartsaudio_audioid FOREIGN KEY (audioid) REFERENCES audio(id);


--
-- TOC entry 2832 (class 2606 OID 22015)
-- Dependencies: 1919 2670 1925
-- Name: fk_cartsaudio_cartstyleid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cartsaudio
    ADD CONSTRAINT fk_cartsaudio_cartstyleid FOREIGN KEY (cartstyleid) REFERENCES cartstyles(id);


--
-- TOC entry 2833 (class 2606 OID 22020)
-- Dependencies: 1919 1926 2672
-- Name: fk_cartsaudio_cartwallid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cartsaudio
    ADD CONSTRAINT fk_cartsaudio_cartwallid FOREIGN KEY (cartwallid) REFERENCES cartwalls(id);


--
-- TOC entry 2836 (class 2606 OID 22025)
-- Dependencies: 1920 2659 1922
-- Name: fk_cartsetgroups_cartsetid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cartsetsgroups
    ADD CONSTRAINT fk_cartsetgroups_cartsetid FOREIGN KEY (cartsetid) REFERENCES cartsets(id);


--
-- TOC entry 2834 (class 2606 OID 22030)
-- Dependencies: 1920 2659 1921
-- Name: fk_cartsetsdir_cartsetid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cartsetsdir
    ADD CONSTRAINT fk_cartsetsdir_cartsetid FOREIGN KEY (cartsetid) REFERENCES cartsets(id);


--
-- TOC entry 2835 (class 2606 OID 22035)
-- Dependencies: 1921 1933 2686
-- Name: fk_cartsetsdir_dirid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cartsetsdir
    ADD CONSTRAINT fk_cartsetsdir_dirid FOREIGN KEY (dirid) REFERENCES dir(id);


--
-- TOC entry 2837 (class 2606 OID 22040)
-- Dependencies: 1922 2702 1941
-- Name: fk_cartsetsgroups_groupid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cartsetsgroups
    ADD CONSTRAINT fk_cartsetsgroups_groupid FOREIGN KEY (groupid) REFERENCES groups(id);


--
-- TOC entry 2838 (class 2606 OID 22045)
-- Dependencies: 1923 2659 1920
-- Name: fk_cartsetsusers_cartsetid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cartsetsusers
    ADD CONSTRAINT fk_cartsetsusers_cartsetid FOREIGN KEY (cartsetid) REFERENCES cartsets(id);


--
-- TOC entry 2839 (class 2606 OID 22050)
-- Dependencies: 2776 1977 1923
-- Name: fk_cartsetsusers_userid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cartsetsusers
    ADD CONSTRAINT fk_cartsetsusers_userid FOREIGN KEY (userid) REFERENCES users(id);


--
-- TOC entry 2840 (class 2606 OID 22055)
-- Dependencies: 1924 2655 1918
-- Name: fk_cartstyleprops_cartpropertyid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cartstyleprops
    ADD CONSTRAINT fk_cartstyleprops_cartpropertyid FOREIGN KEY (cartpropertyid) REFERENCES cartproperties(id);


--
-- TOC entry 2841 (class 2606 OID 22060)
-- Dependencies: 1924 2670 1925
-- Name: fk_cartstyleprops_cartstyleid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cartstyleprops
    ADD CONSTRAINT fk_cartstyleprops_cartstyleid FOREIGN KEY (cartstyleid) REFERENCES cartstyles(id);


--
-- TOC entry 2842 (class 2606 OID 22065)
-- Dependencies: 1920 1926 2659
-- Name: fk_cartwalls_cartsetid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cartwalls
    ADD CONSTRAINT fk_cartwalls_cartsetid FOREIGN KEY (cartsetid) REFERENCES cartsets(id);


--
-- TOC entry 2843 (class 2606 OID 22070)
-- Dependencies: 1927 2776 1977
-- Name: fk_changelog_userid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY changelog
    ADD CONSTRAINT fk_changelog_userid FOREIGN KEY (userid) REFERENCES users(id);


--
-- TOC entry 2844 (class 2606 OID 22075)
-- Dependencies: 1928 1929 2678
-- Name: fk_cmscontent_regionid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cmscontent
    ADD CONSTRAINT fk_cmscontent_regionid FOREIGN KEY (regionid) REFERENCES cmsregions(regionid);


--
-- TOC entry 2845 (class 2606 OID 22080)
-- Dependencies: 1928 2776 1977
-- Name: fk_cmscontent_userid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cmscontent
    ADD CONSTRAINT fk_cmscontent_userid FOREIGN KEY (userid) REFERENCES users(id);


--
-- TOC entry 2846 (class 2606 OID 22085)
-- Dependencies: 1951 2722 1929
-- Name: fk_cmsregions_editrealm; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cmsregions
    ADD CONSTRAINT fk_cmsregions_editrealm FOREIGN KEY (editrealm) REFERENCES realms(realmid);


--
-- TOC entry 2847 (class 2606 OID 22090)
-- Dependencies: 2722 1929 1951
-- Name: fk_cmsregions_viewrealm; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY cmsregions
    ADD CONSTRAINT fk_cmsregions_viewrealm FOREIGN KEY (viewrealm) REFERENCES realms(realmid);


--
-- TOC entry 2848 (class 2606 OID 22095)
-- Dependencies: 1934 1933 2686
-- Name: fk_dirgroups_dirid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY dirgroups
    ADD CONSTRAINT fk_dirgroups_dirid FOREIGN KEY (dirid) REFERENCES dir(id);


--
-- TOC entry 2849 (class 2606 OID 22100)
-- Dependencies: 1934 1941 2702
-- Name: fk_dirgroups_groupid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY dirgroups
    ADD CONSTRAINT fk_dirgroups_groupid FOREIGN KEY (groupid) REFERENCES groups(id);


--
-- TOC entry 2851 (class 2606 OID 22105)
-- Dependencies: 1977 2776 1935
-- Name: fk_dirusers_userid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY dirusers
    ADD CONSTRAINT fk_dirusers_userid FOREIGN KEY (userid) REFERENCES users(id);


--
-- TOC entry 2852 (class 2606 OID 22110)
-- Dependencies: 1939 2696 1938
-- Name: fk_formfields_ruleid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY formfields
    ADD CONSTRAINT fk_formfields_ruleid FOREIGN KEY (ruleid) REFERENCES fieldvalidators(ruleid);


--
-- TOC entry 2853 (class 2606 OID 22115)
-- Dependencies: 1940 1951 2722
-- Name: fk_forms_realmid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY forms
    ADD CONSTRAINT fk_forms_realmid FOREIGN KEY (realmid) REFERENCES realms(realmid);


--
-- TOC entry 2854 (class 2606 OID 22120)
-- Dependencies: 1946 1977 2776
-- Name: fk_log_userid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY log
    ADD CONSTRAINT fk_log_userid FOREIGN KEY (userid) REFERENCES users(id);


--
-- TOC entry 2896 (class 2606 OID 22357)
-- Dependencies: 2115 2776 1977
-- Name: fk_news_creator; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY news
    ADD CONSTRAINT fk_news_creator FOREIGN KEY (creator) REFERENCES users(id);


--
-- TOC entry 2855 (class 2606 OID 22125)
-- Dependencies: 1950 1941 2702
-- Name: fk_realmgrouplink_groupid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY realmgrouplink
    ADD CONSTRAINT fk_realmgrouplink_groupid FOREIGN KEY (groupid) REFERENCES groups(id);


--
-- TOC entry 2856 (class 2606 OID 22130)
-- Dependencies: 1950 1951 2722
-- Name: fk_realmgrouplink_realmid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY realmgrouplink
    ADD CONSTRAINT fk_realmgrouplink_realmid FOREIGN KEY (realmid) REFERENCES realms(realmid);


--
-- TOC entry 2857 (class 2606 OID 22135)
-- Dependencies: 1952 1951 2722
-- Name: fk_realmuserlink_realmid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY realmuserlink
    ADD CONSTRAINT fk_realmuserlink_realmid FOREIGN KEY (realmid) REFERENCES realms(realmid);


--
-- TOC entry 2858 (class 2606 OID 22140)
-- Dependencies: 1952 1977 2776
-- Name: fk_realuserlink_userid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY realmuserlink
    ADD CONSTRAINT fk_realuserlink_userid FOREIGN KEY (userid) REFERENCES users(id);


--
-- TOC entry 2859 (class 2606 OID 22145)
-- Dependencies: 1977 1953 2776
-- Name: fk_requests_userid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY requests
    ADD CONSTRAINT fk_requests_userid FOREIGN KEY (userid) REFERENCES users(id);


--
-- TOC entry 2860 (class 2606 OID 22150)
-- Dependencies: 2776 1977 1954
-- Name: fk_scripts_userid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY scripts
    ADD CONSTRAINT fk_scripts_userid FOREIGN KEY (userid) REFERENCES users(id);


--
-- TOC entry 2861 (class 2606 OID 22155)
-- Dependencies: 2686 1955 1933
-- Name: fk_scriptsdir_dirid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY scriptsdir
    ADD CONSTRAINT fk_scriptsdir_dirid FOREIGN KEY (dirid) REFERENCES dir(id);


--
-- TOC entry 2862 (class 2606 OID 22160)
-- Dependencies: 1954 1955 2728
-- Name: fk_scriptsdir_scriptid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY scriptsdir
    ADD CONSTRAINT fk_scriptsdir_scriptid FOREIGN KEY (scriptid) REFERENCES scripts(id);


--
-- TOC entry 2863 (class 2606 OID 22165)
-- Dependencies: 1956 1941 2702
-- Name: fk_scriptsgroups_groupid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY scriptsgroups
    ADD CONSTRAINT fk_scriptsgroups_groupid FOREIGN KEY (groupid) REFERENCES groups(id);


--
-- TOC entry 2864 (class 2606 OID 22170)
-- Dependencies: 1956 1954 2728
-- Name: fk_scriptsgroups_scriptid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY scriptsgroups
    ADD CONSTRAINT fk_scriptsgroups_scriptid FOREIGN KEY (scriptid) REFERENCES scripts(id);


--
-- TOC entry 2865 (class 2606 OID 22175)
-- Dependencies: 1957 1954 2728
-- Name: fk_scriptsusers_scriptid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY scriptsusers
    ADD CONSTRAINT fk_scriptsusers_scriptid FOREIGN KEY (scriptid) REFERENCES scripts(id);


--
-- TOC entry 2866 (class 2606 OID 22180)
-- Dependencies: 1957 1977 2776
-- Name: fk_scriptsusers_userid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY scriptsusers
    ADD CONSTRAINT fk_scriptsusers_userid FOREIGN KEY (userid) REFERENCES users(id);


--
-- TOC entry 2867 (class 2606 OID 22185)
-- Dependencies: 1958 1959 2737
-- Name: fk_sessionvalues_sessionid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY sessionvalues
    ADD CONSTRAINT fk_sessionvalues_sessionid FOREIGN KEY (sessionid) REFERENCES sessions(sessionid);


--
-- TOC entry 2868 (class 2606 OID 22190)
-- Dependencies: 2728 1954 1960
-- Name: fk_showitems_scriptid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY showitems
    ADD CONSTRAINT fk_showitems_scriptid FOREIGN KEY (scriptid) REFERENCES scripts(id);


--
-- TOC entry 2869 (class 2606 OID 22195)
-- Dependencies: 2747 1960 1963
-- Name: fk_showitems_showplanid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY showitems
    ADD CONSTRAINT fk_showitems_showplanid FOREIGN KEY (showplanid) REFERENCES showplans(id);


--
-- TOC entry 2875 (class 2606 OID 22200)
-- Dependencies: 2686 1933 1964
-- Name: fk_showplandir; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY showplansdir
    ADD CONSTRAINT fk_showplandir FOREIGN KEY (dirid) REFERENCES dir(id);


--
-- TOC entry 2871 (class 2606 OID 22205)
-- Dependencies: 1961 2686 1933
-- Name: fk_showplandir; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY showplandir
    ADD CONSTRAINT fk_showplandir FOREIGN KEY (dirid) REFERENCES dir(id);


--
-- TOC entry 2876 (class 2606 OID 22210)
-- Dependencies: 2747 1963 1964
-- Name: fk_showplandir_showplanid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY showplansdir
    ADD CONSTRAINT fk_showplandir_showplanid FOREIGN KEY (showplanid) REFERENCES showplans(id);


--
-- TOC entry 2872 (class 2606 OID 22215)
-- Dependencies: 2747 1963 1961
-- Name: fk_showplandir_showplanid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY showplandir
    ADD CONSTRAINT fk_showplandir_showplanid FOREIGN KEY (showplanid) REFERENCES showplans(id);


--
-- TOC entry 2877 (class 2606 OID 22220)
-- Dependencies: 2702 1941 1965
-- Name: fk_showplangroups_groupid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY showplansgroups
    ADD CONSTRAINT fk_showplangroups_groupid FOREIGN KEY (groupid) REFERENCES groups(id);


--
-- TOC entry 2873 (class 2606 OID 22225)
-- Dependencies: 1962 2702 1941
-- Name: fk_showplangroups_groupid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY showplangroups
    ADD CONSTRAINT fk_showplangroups_groupid FOREIGN KEY (groupid) REFERENCES groups(id);


--
-- TOC entry 2878 (class 2606 OID 22230)
-- Dependencies: 2747 1963 1965
-- Name: fk_showplangroups_showplanid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY showplansgroups
    ADD CONSTRAINT fk_showplangroups_showplanid FOREIGN KEY (showplanid) REFERENCES showplans(id);


--
-- TOC entry 2874 (class 2606 OID 22235)
-- Dependencies: 1962 1963 2747
-- Name: fk_showplangroups_showplanid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY showplangroups
    ADD CONSTRAINT fk_showplangroups_showplanid FOREIGN KEY (showplanid) REFERENCES showplans(id);


--
-- TOC entry 2870 (class 2606 OID 22240)
-- Dependencies: 2599 1960 1892
-- Name: fk_showplanitems_audioid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY showitems
    ADD CONSTRAINT fk_showplanitems_audioid FOREIGN KEY (audioid) REFERENCES audio(id);


--
-- TOC entry 2879 (class 2606 OID 22245)
-- Dependencies: 1966 2747 1963
-- Name: fk_showplanusers_showplanid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY showplansusers
    ADD CONSTRAINT fk_showplanusers_showplanid FOREIGN KEY (showplanid) REFERENCES showplans(id);


--
-- TOC entry 2881 (class 2606 OID 22250)
-- Dependencies: 1967 2747 1963
-- Name: fk_showplanusers_showplanid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY showplanusers
    ADD CONSTRAINT fk_showplanusers_showplanid FOREIGN KEY (showplanid) REFERENCES showplans(id);


--
-- TOC entry 2880 (class 2606 OID 22255)
-- Dependencies: 1977 1966 2776
-- Name: fk_showplanusers_userid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY showplansusers
    ADD CONSTRAINT fk_showplanusers_userid FOREIGN KEY (userid) REFERENCES users(id);


--
-- TOC entry 2882 (class 2606 OID 22260)
-- Dependencies: 2776 1977 1967
-- Name: fk_showplanusers_userid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY showplanusers
    ADD CONSTRAINT fk_showplanusers_userid FOREIGN KEY (userid) REFERENCES users(id);


--
-- TOC entry 2883 (class 2606 OID 22265)
-- Dependencies: 1968 2694 1937
-- Name: fk_sustschedule_extfeedid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY sustschedule
    ADD CONSTRAINT fk_sustschedule_extfeedid FOREIGN KEY (extfeedid) REFERENCES extfeeds(id);


--
-- TOC entry 2884 (class 2606 OID 22270)
-- Dependencies: 2760 1969 1970
-- Name: fk_taskschedule_taskid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY taskschedule
    ADD CONSTRAINT fk_taskschedule_taskid FOREIGN KEY (taskid) REFERENCES tasks(id);


--
-- TOC entry 2885 (class 2606 OID 22275)
-- Dependencies: 1971 2722 1951
-- Name: fk_templates_realmid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY templates
    ADD CONSTRAINT fk_templates_realmid FOREIGN KEY (realmid) REFERENCES realms(realmid);


--
-- TOC entry 2886 (class 2606 OID 22280)
-- Dependencies: 2770 1973 1974
-- Name: fk_txschedule_showid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY txschedule
    ADD CONSTRAINT fk_txschedule_showid FOREIGN KEY (txshowid) REFERENCES txshows(id);


--
-- TOC entry 2887 (class 2606 OID 22285)
-- Dependencies: 1972 1974 2766
-- Name: fk_txshows_txcategoryid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY txshows
    ADD CONSTRAINT fk_txshows_txcategoryid FOREIGN KEY (txcategoryid) REFERENCES txcategories(id);


--
-- TOC entry 2888 (class 2606 OID 22290)
-- Dependencies: 1944 1975 2708
-- Name: fk_txshowskeywords; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY txshowskeywords
    ADD CONSTRAINT fk_txshowskeywords FOREIGN KEY (keywordid) REFERENCES keywords(id);


--
-- TOC entry 2889 (class 2606 OID 22295)
-- Dependencies: 2770 1974 1975
-- Name: fk_txshowskeywords_txshowid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY txshowskeywords
    ADD CONSTRAINT fk_txshowskeywords_txshowid FOREIGN KEY (txshowid) REFERENCES txshows(id);


--
-- TOC entry 2890 (class 2606 OID 22300)
-- Dependencies: 1974 1976 2770
-- Name: fk_txshowsusers_txshowid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY txshowsusers
    ADD CONSTRAINT fk_txshowsusers_txshowid FOREIGN KEY (txshowid) REFERENCES txshows(id);


--
-- TOC entry 2891 (class 2606 OID 22305)
-- Dependencies: 2776 1976 1977
-- Name: fk_txshowsusers_userid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY txshowsusers
    ADD CONSTRAINT fk_txshowsusers_userid FOREIGN KEY (userid) REFERENCES users(id);


--
-- TOC entry 2892 (class 2606 OID 22310)
-- Dependencies: 2682 1978 1931
-- Name: fk_userconfigs_configid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY usersconfigs
    ADD CONSTRAINT fk_userconfigs_configid FOREIGN KEY (configid) REFERENCES configs(id);


--
-- TOC entry 2893 (class 2606 OID 22315)
-- Dependencies: 2776 1978 1977
-- Name: fk_userconfigs_userid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY usersconfigs
    ADD CONSTRAINT fk_userconfigs_userid FOREIGN KEY (userid) REFERENCES users(id);


--
-- TOC entry 2894 (class 2606 OID 22320)
-- Dependencies: 2702 1941 1979
-- Name: fk_usersgroups_groupid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY usersgroups
    ADD CONSTRAINT fk_usersgroups_groupid FOREIGN KEY (groupid) REFERENCES groups(id);


--
-- TOC entry 2895 (class 2606 OID 22325)
-- Dependencies: 2776 1979 1977
-- Name: fk_usersgroups_userid; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY usersgroups
    ADD CONSTRAINT fk_usersgroups_userid FOREIGN KEY (userid) REFERENCES users(id);


--
-- TOC entry 2910 (class 0 OID 0)
-- Dependencies: 6
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;
GRANT ALL ON SCHEMA public TO dps;


--
-- TOC entry 2911 (class 0 OID 0)
-- Dependencies: 1887
-- Name: advertschedule; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE advertschedule FROM PUBLIC;
REVOKE ALL ON TABLE advertschedule FROM postgres;
GRANT ALL ON TABLE advertschedule TO postgres;
GRANT ALL ON TABLE advertschedule TO dps;


--
-- TOC entry 2912 (class 0 OID 0)
-- Dependencies: 1888
-- Name: albums; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE albums FROM PUBLIC;
REVOKE ALL ON TABLE albums FROM postgres;
GRANT ALL ON TABLE albums TO postgres;
GRANT ALL ON TABLE albums TO dps;


--
-- TOC entry 2913 (class 0 OID 0)
-- Dependencies: 1889
-- Name: archives; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE archives FROM PUBLIC;
REVOKE ALL ON TABLE archives FROM postgres;
GRANT ALL ON TABLE archives TO postgres;
GRANT ALL ON TABLE archives TO dps;


--
-- TOC entry 2914 (class 0 OID 0)
-- Dependencies: 1890
-- Name: artists; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE artists FROM PUBLIC;
REVOKE ALL ON TABLE artists FROM postgres;
GRANT ALL ON TABLE artists TO postgres;
GRANT ALL ON TABLE artists TO dps;


--
-- TOC entry 2915 (class 0 OID 0)
-- Dependencies: 1891
-- Name: artistskeywords; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE artistskeywords FROM PUBLIC;
REVOKE ALL ON TABLE artistskeywords FROM postgres;
GRANT ALL ON TABLE artistskeywords TO postgres;
GRANT ALL ON TABLE artistskeywords TO dps;


--
-- TOC entry 2916 (class 0 OID 0)
-- Dependencies: 1892
-- Name: audio; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE audio FROM PUBLIC;
REVOKE ALL ON TABLE audio FROM postgres;
GRANT ALL ON TABLE audio TO postgres;
GRANT ALL ON TABLE audio TO dps;


--
-- TOC entry 2917 (class 0 OID 0)
-- Dependencies: 1893
-- Name: audioartists; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE audioartists FROM PUBLIC;
REVOKE ALL ON TABLE audioartists FROM postgres;
GRANT ALL ON TABLE audioartists TO postgres;
GRANT ALL ON TABLE audioartists TO dps;


--
-- TOC entry 2918 (class 0 OID 0)
-- Dependencies: 1894
-- Name: audiocomments; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE audiocomments FROM PUBLIC;
REVOKE ALL ON TABLE audiocomments FROM postgres;
GRANT ALL ON TABLE audiocomments TO postgres;
GRANT ALL ON TABLE audiocomments TO dps;


--
-- TOC entry 2919 (class 0 OID 0)
-- Dependencies: 1895
-- Name: audiodir; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE audiodir FROM PUBLIC;
REVOKE ALL ON TABLE audiodir FROM postgres;
GRANT ALL ON TABLE audiodir TO postgres;
GRANT ALL ON TABLE audiodir TO dps;


--
-- TOC entry 2920 (class 0 OID 0)
-- Dependencies: 1896
-- Name: audioext; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE audioext FROM PUBLIC;
REVOKE ALL ON TABLE audioext FROM postgres;
GRANT ALL ON TABLE audioext TO postgres;
GRANT ALL ON TABLE audioext TO dps;


--
-- TOC entry 2921 (class 0 OID 0)
-- Dependencies: 1897
-- Name: audiogroups; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE audiogroups FROM PUBLIC;
REVOKE ALL ON TABLE audiogroups FROM postgres;
GRANT ALL ON TABLE audiogroups TO postgres;
GRANT ALL ON TABLE audiogroups TO dps;


--
-- TOC entry 2922 (class 0 OID 0)
-- Dependencies: 1898
-- Name: audiojinglepkgs; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE audiojinglepkgs FROM PUBLIC;
REVOKE ALL ON TABLE audiojinglepkgs FROM postgres;
GRANT ALL ON TABLE audiojinglepkgs TO postgres;
GRANT ALL ON TABLE audiojinglepkgs TO dps;


--
-- TOC entry 2923 (class 0 OID 0)
-- Dependencies: 1899
-- Name: audiokeywords; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE audiokeywords FROM PUBLIC;
REVOKE ALL ON TABLE audiokeywords FROM postgres;
GRANT ALL ON TABLE audiokeywords TO postgres;
GRANT ALL ON TABLE audiokeywords TO dps;


--
-- TOC entry 2924 (class 0 OID 0)
-- Dependencies: 1900
-- Name: audiolog; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE audiolog FROM PUBLIC;
REVOKE ALL ON TABLE audiolog FROM postgres;
GRANT ALL ON TABLE audiolog TO postgres;
GRANT ALL ON TABLE audiolog TO dps;


--
-- TOC entry 2925 (class 0 OID 0)
-- Dependencies: 1901
-- Name: audioplaylists; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE audioplaylists FROM PUBLIC;
REVOKE ALL ON TABLE audioplaylists FROM postgres;
GRANT ALL ON TABLE audioplaylists TO postgres;
GRANT ALL ON TABLE audioplaylists TO dps;


--
-- TOC entry 2926 (class 0 OID 0)
-- Dependencies: 1902
-- Name: audiotypes; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE audiotypes FROM PUBLIC;
REVOKE ALL ON TABLE audiotypes FROM postgres;
GRANT ALL ON TABLE audiotypes TO postgres;
GRANT ALL ON TABLE audiotypes TO dps;


--
-- TOC entry 2927 (class 0 OID 0)
-- Dependencies: 1903
-- Name: audiousers; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE audiousers FROM PUBLIC;
REVOKE ALL ON TABLE audiousers FROM postgres;
GRANT ALL ON TABLE audiousers TO postgres;
GRANT ALL ON TABLE audiousers TO dps;


--
-- TOC entry 2928 (class 0 OID 0)
-- Dependencies: 1904
-- Name: aw_items; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE aw_items FROM PUBLIC;
REVOKE ALL ON TABLE aw_items FROM postgres;
GRANT ALL ON TABLE aw_items TO postgres;
GRANT ALL ON TABLE aw_items TO dps;


--
-- TOC entry 2929 (class 0 OID 0)
-- Dependencies: 1905
-- Name: aw_props; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE aw_props FROM PUBLIC;
REVOKE ALL ON TABLE aw_props FROM postgres;
GRANT ALL ON TABLE aw_props TO postgres;
GRANT ALL ON TABLE aw_props TO dps;


--
-- TOC entry 2930 (class 0 OID 0)
-- Dependencies: 1906
-- Name: aw_sets; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE aw_sets FROM PUBLIC;
REVOKE ALL ON TABLE aw_sets FROM postgres;
GRANT ALL ON TABLE aw_sets TO postgres;
GRANT ALL ON TABLE aw_sets TO dps;


--
-- TOC entry 2931 (class 0 OID 0)
-- Dependencies: 1907
-- Name: aw_sets_dir; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE aw_sets_dir FROM PUBLIC;
REVOKE ALL ON TABLE aw_sets_dir FROM postgres;
GRANT ALL ON TABLE aw_sets_dir TO postgres;
GRANT ALL ON TABLE aw_sets_dir TO dps;


--
-- TOC entry 2932 (class 0 OID 0)
-- Dependencies: 1908
-- Name: aw_sets_groups; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE aw_sets_groups FROM PUBLIC;
REVOKE ALL ON TABLE aw_sets_groups FROM postgres;
GRANT ALL ON TABLE aw_sets_groups TO postgres;
GRANT ALL ON TABLE aw_sets_groups TO dps;


--
-- TOC entry 2933 (class 0 OID 0)
-- Dependencies: 1909
-- Name: aw_sets_users; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE aw_sets_users FROM PUBLIC;
REVOKE ALL ON TABLE aw_sets_users FROM postgres;
GRANT ALL ON TABLE aw_sets_users TO postgres;
GRANT ALL ON TABLE aw_sets_users TO dps;


--
-- TOC entry 2934 (class 0 OID 0)
-- Dependencies: 1910
-- Name: aw_styles; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE aw_styles FROM PUBLIC;
REVOKE ALL ON TABLE aw_styles FROM postgres;
GRANT ALL ON TABLE aw_styles TO postgres;
GRANT ALL ON TABLE aw_styles TO dps;


--
-- TOC entry 2935 (class 0 OID 0)
-- Dependencies: 1911
-- Name: aw_styles_props; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE aw_styles_props FROM PUBLIC;
REVOKE ALL ON TABLE aw_styles_props FROM postgres;
GRANT ALL ON TABLE aw_styles_props TO postgres;
GRANT ALL ON TABLE aw_styles_props TO dps;


--
-- TOC entry 2936 (class 0 OID 0)
-- Dependencies: 1912
-- Name: aw_walls; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE aw_walls FROM PUBLIC;
REVOKE ALL ON TABLE aw_walls FROM postgres;
GRANT ALL ON TABLE aw_walls TO postgres;
GRANT ALL ON TABLE aw_walls TO dps;


--
-- TOC entry 2937 (class 0 OID 0)
-- Dependencies: 1913
-- Name: bins; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE bins FROM PUBLIC;
REVOKE ALL ON TABLE bins FROM postgres;
GRANT ALL ON TABLE bins TO postgres;
GRANT ALL ON TABLE bins TO dps;


--
-- TOC entry 2938 (class 0 OID 0)
-- Dependencies: 1914
-- Name: binsartists; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE binsartists FROM PUBLIC;
REVOKE ALL ON TABLE binsartists FROM postgres;
GRANT ALL ON TABLE binsartists TO postgres;
GRANT ALL ON TABLE binsartists TO dps;


--
-- TOC entry 2939 (class 0 OID 0)
-- Dependencies: 1915
-- Name: binsaudio; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE binsaudio FROM PUBLIC;
REVOKE ALL ON TABLE binsaudio FROM postgres;
GRANT ALL ON TABLE binsaudio TO postgres;
GRANT ALL ON TABLE binsaudio TO dps;


--
-- TOC entry 2940 (class 0 OID 0)
-- Dependencies: 1916
-- Name: binskeywords; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE binskeywords FROM PUBLIC;
REVOKE ALL ON TABLE binskeywords FROM postgres;
GRANT ALL ON TABLE binskeywords TO postgres;
GRANT ALL ON TABLE binskeywords TO dps;


--
-- TOC entry 2941 (class 0 OID 0)
-- Dependencies: 1917
-- Name: binsschedule; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE binsschedule FROM PUBLIC;
REVOKE ALL ON TABLE binsschedule FROM postgres;
GRANT ALL ON TABLE binsschedule TO postgres;
GRANT ALL ON TABLE binsschedule TO dps;


--
-- TOC entry 2942 (class 0 OID 0)
-- Dependencies: 1918
-- Name: cartproperties; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE cartproperties FROM PUBLIC;
REVOKE ALL ON TABLE cartproperties FROM postgres;
GRANT ALL ON TABLE cartproperties TO postgres;
GRANT ALL ON TABLE cartproperties TO dps;


--
-- TOC entry 2943 (class 0 OID 0)
-- Dependencies: 1919
-- Name: cartsaudio; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE cartsaudio FROM PUBLIC;
REVOKE ALL ON TABLE cartsaudio FROM postgres;
GRANT ALL ON TABLE cartsaudio TO postgres;
GRANT ALL ON TABLE cartsaudio TO dps;


--
-- TOC entry 2944 (class 0 OID 0)
-- Dependencies: 1920
-- Name: cartsets; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE cartsets FROM PUBLIC;
REVOKE ALL ON TABLE cartsets FROM postgres;
GRANT ALL ON TABLE cartsets TO postgres;
GRANT ALL ON TABLE cartsets TO dps;


--
-- TOC entry 2945 (class 0 OID 0)
-- Dependencies: 1921
-- Name: cartsetsdir; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE cartsetsdir FROM PUBLIC;
REVOKE ALL ON TABLE cartsetsdir FROM postgres;
GRANT ALL ON TABLE cartsetsdir TO postgres;
GRANT ALL ON TABLE cartsetsdir TO dps;


--
-- TOC entry 2946 (class 0 OID 0)
-- Dependencies: 1922
-- Name: cartsetsgroups; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE cartsetsgroups FROM PUBLIC;
REVOKE ALL ON TABLE cartsetsgroups FROM postgres;
GRANT ALL ON TABLE cartsetsgroups TO postgres;
GRANT ALL ON TABLE cartsetsgroups TO dps;


--
-- TOC entry 2947 (class 0 OID 0)
-- Dependencies: 1923
-- Name: cartsetsusers; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE cartsetsusers FROM PUBLIC;
REVOKE ALL ON TABLE cartsetsusers FROM postgres;
GRANT ALL ON TABLE cartsetsusers TO postgres;
GRANT ALL ON TABLE cartsetsusers TO dps;


--
-- TOC entry 2948 (class 0 OID 0)
-- Dependencies: 1924
-- Name: cartstyleprops; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE cartstyleprops FROM PUBLIC;
REVOKE ALL ON TABLE cartstyleprops FROM postgres;
GRANT ALL ON TABLE cartstyleprops TO postgres;
GRANT ALL ON TABLE cartstyleprops TO dps;


--
-- TOC entry 2949 (class 0 OID 0)
-- Dependencies: 1925
-- Name: cartstyles; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE cartstyles FROM PUBLIC;
REVOKE ALL ON TABLE cartstyles FROM postgres;
GRANT ALL ON TABLE cartstyles TO postgres;
GRANT ALL ON TABLE cartstyles TO dps;


--
-- TOC entry 2950 (class 0 OID 0)
-- Dependencies: 1926
-- Name: cartwalls; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE cartwalls FROM PUBLIC;
REVOKE ALL ON TABLE cartwalls FROM postgres;
GRANT ALL ON TABLE cartwalls TO postgres;
GRANT ALL ON TABLE cartwalls TO dps;


--
-- TOC entry 2951 (class 0 OID 0)
-- Dependencies: 1927
-- Name: changelog; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE changelog FROM PUBLIC;
REVOKE ALL ON TABLE changelog FROM postgres;
GRANT ALL ON TABLE changelog TO postgres;
GRANT ALL ON TABLE changelog TO dps;


--
-- TOC entry 2952 (class 0 OID 0)
-- Dependencies: 1928
-- Name: cmscontent; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE cmscontent FROM PUBLIC;
REVOKE ALL ON TABLE cmscontent FROM postgres;
GRANT ALL ON TABLE cmscontent TO postgres;
GRANT ALL ON TABLE cmscontent TO dps;


--
-- TOC entry 2953 (class 0 OID 0)
-- Dependencies: 1929
-- Name: cmsregions; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE cmsregions FROM PUBLIC;
REVOKE ALL ON TABLE cmsregions FROM postgres;
GRANT ALL ON TABLE cmsregions TO postgres;
GRANT ALL ON TABLE cmsregions TO dps;


--
-- TOC entry 2954 (class 0 OID 0)
-- Dependencies: 1930
-- Name: companies; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE companies FROM PUBLIC;
REVOKE ALL ON TABLE companies FROM postgres;
GRANT ALL ON TABLE companies TO postgres;
GRANT ALL ON TABLE companies TO dps;


--
-- TOC entry 2955 (class 0 OID 0)
-- Dependencies: 1931
-- Name: configs; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE configs FROM PUBLIC;
REVOKE ALL ON TABLE configs FROM postgres;
GRANT ALL ON TABLE configs TO postgres;
GRANT ALL ON TABLE configs TO dps;


--
-- TOC entry 2956 (class 0 OID 0)
-- Dependencies: 1932
-- Name: configuration; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE configuration FROM PUBLIC;
REVOKE ALL ON TABLE configuration FROM postgres;
GRANT ALL ON TABLE configuration TO postgres;
GRANT ALL ON TABLE configuration TO dps;


--
-- TOC entry 2957 (class 0 OID 0)
-- Dependencies: 1933
-- Name: dir; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE dir FROM PUBLIC;
REVOKE ALL ON TABLE dir FROM postgres;
GRANT ALL ON TABLE dir TO postgres;
GRANT ALL ON TABLE dir TO dps;


--
-- TOC entry 2958 (class 0 OID 0)
-- Dependencies: 1934
-- Name: dirgroups; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE dirgroups FROM PUBLIC;
REVOKE ALL ON TABLE dirgroups FROM postgres;
GRANT ALL ON TABLE dirgroups TO postgres;
GRANT ALL ON TABLE dirgroups TO dps;


--
-- TOC entry 2959 (class 0 OID 0)
-- Dependencies: 1935
-- Name: dirusers; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE dirusers FROM PUBLIC;
REVOKE ALL ON TABLE dirusers FROM postgres;
GRANT ALL ON TABLE dirusers TO postgres;
GRANT ALL ON TABLE dirusers TO dps;


--
-- TOC entry 2960 (class 0 OID 0)
-- Dependencies: 1936
-- Name: email; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE email FROM PUBLIC;
REVOKE ALL ON TABLE email FROM postgres;
GRANT ALL ON TABLE email TO postgres;
GRANT ALL ON TABLE email TO dps;


--
-- TOC entry 2961 (class 0 OID 0)
-- Dependencies: 1937
-- Name: extfeeds; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE extfeeds FROM PUBLIC;
REVOKE ALL ON TABLE extfeeds FROM postgres;
GRANT ALL ON TABLE extfeeds TO postgres;
GRANT ALL ON TABLE extfeeds TO dps;


--
-- TOC entry 2962 (class 0 OID 0)
-- Dependencies: 1938
-- Name: fieldvalidators; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE fieldvalidators FROM PUBLIC;
REVOKE ALL ON TABLE fieldvalidators FROM postgres;
GRANT ALL ON TABLE fieldvalidators TO postgres;
GRANT ALL ON TABLE fieldvalidators TO dps;


--
-- TOC entry 2963 (class 0 OID 0)
-- Dependencies: 1939
-- Name: formfields; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE formfields FROM PUBLIC;
REVOKE ALL ON TABLE formfields FROM postgres;
GRANT ALL ON TABLE formfields TO postgres;
GRANT ALL ON TABLE formfields TO dps;


--
-- TOC entry 2964 (class 0 OID 0)
-- Dependencies: 1940
-- Name: forms; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE forms FROM PUBLIC;
REVOKE ALL ON TABLE forms FROM postgres;
GRANT ALL ON TABLE forms TO postgres;
GRANT ALL ON TABLE forms TO dps;


--
-- TOC entry 2965 (class 0 OID 0)
-- Dependencies: 1941
-- Name: groups; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE groups FROM PUBLIC;
REVOKE ALL ON TABLE groups FROM postgres;
GRANT ALL ON TABLE groups TO postgres;
GRANT ALL ON TABLE groups TO dps;


--
-- TOC entry 2966 (class 0 OID 0)
-- Dependencies: 1942
-- Name: jinglepkgs; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE jinglepkgs FROM PUBLIC;
REVOKE ALL ON TABLE jinglepkgs FROM postgres;
GRANT ALL ON TABLE jinglepkgs TO postgres;
GRANT ALL ON TABLE jinglepkgs TO dps;


--
-- TOC entry 2967 (class 0 OID 0)
-- Dependencies: 1943
-- Name: jingletypes; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE jingletypes FROM PUBLIC;
REVOKE ALL ON TABLE jingletypes FROM postgres;
GRANT ALL ON TABLE jingletypes TO postgres;
GRANT ALL ON TABLE jingletypes TO dps;


--
-- TOC entry 2968 (class 0 OID 0)
-- Dependencies: 1944
-- Name: keywords; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE keywords FROM PUBLIC;
REVOKE ALL ON TABLE keywords FROM postgres;
GRANT ALL ON TABLE keywords TO postgres;
GRANT ALL ON TABLE keywords TO dps;


--
-- TOC entry 2969 (class 0 OID 0)
-- Dependencies: 1945
-- Name: lifespans; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE lifespans FROM PUBLIC;
REVOKE ALL ON TABLE lifespans FROM postgres;
GRANT ALL ON TABLE lifespans TO postgres;
GRANT ALL ON TABLE lifespans TO dps;


--
-- TOC entry 2970 (class 0 OID 0)
-- Dependencies: 1946
-- Name: log; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE log FROM PUBLIC;
REVOKE ALL ON TABLE log FROM postgres;
GRANT ALL ON TABLE log TO postgres;
GRANT ALL ON TABLE log TO dps;


--
-- TOC entry 2971 (class 0 OID 0)
-- Dependencies: 1947
-- Name: logentries; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE logentries FROM PUBLIC;
REVOKE ALL ON TABLE logentries FROM postgres;
GRANT ALL ON TABLE logentries TO postgres;
GRANT ALL ON TABLE logentries TO dps;


--
-- TOC entry 2972 (class 0 OID 0)
-- Dependencies: 2115
-- Name: news; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE news FROM PUBLIC;
REVOKE ALL ON TABLE news FROM postgres;
GRANT ALL ON TABLE news TO postgres;
GRANT ALL ON TABLE news TO dps;


--
-- TOC entry 2973 (class 0 OID 0)
-- Dependencies: 1948
-- Name: patches; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE patches FROM PUBLIC;
REVOKE ALL ON TABLE patches FROM postgres;
GRANT ALL ON TABLE patches TO postgres;
GRANT ALL ON TABLE patches TO dps;


--
-- TOC entry 2974 (class 0 OID 0)
-- Dependencies: 1949
-- Name: playlists; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE playlists FROM PUBLIC;
REVOKE ALL ON TABLE playlists FROM postgres;
GRANT ALL ON TABLE playlists TO postgres;
GRANT ALL ON TABLE playlists TO dps;


--
-- TOC entry 2975 (class 0 OID 0)
-- Dependencies: 1950
-- Name: realmgrouplink; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE realmgrouplink FROM PUBLIC;
REVOKE ALL ON TABLE realmgrouplink FROM postgres;
GRANT ALL ON TABLE realmgrouplink TO postgres;
GRANT ALL ON TABLE realmgrouplink TO dps;


--
-- TOC entry 2976 (class 0 OID 0)
-- Dependencies: 1951
-- Name: realms; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE realms FROM PUBLIC;
REVOKE ALL ON TABLE realms FROM postgres;
GRANT ALL ON TABLE realms TO postgres;
GRANT ALL ON TABLE realms TO dps;


--
-- TOC entry 2977 (class 0 OID 0)
-- Dependencies: 1952
-- Name: realmuserlink; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE realmuserlink FROM PUBLIC;
REVOKE ALL ON TABLE realmuserlink FROM postgres;
GRANT ALL ON TABLE realmuserlink TO postgres;
GRANT ALL ON TABLE realmuserlink TO dps;


--
-- TOC entry 2978 (class 0 OID 0)
-- Dependencies: 1953
-- Name: requests; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE requests FROM PUBLIC;
REVOKE ALL ON TABLE requests FROM postgres;
GRANT ALL ON TABLE requests TO postgres;
GRANT ALL ON TABLE requests TO dps;


--
-- TOC entry 2979 (class 0 OID 0)
-- Dependencies: 1954
-- Name: scripts; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE scripts FROM PUBLIC;
REVOKE ALL ON TABLE scripts FROM postgres;
GRANT ALL ON TABLE scripts TO postgres;
GRANT ALL ON TABLE scripts TO dps;


--
-- TOC entry 2980 (class 0 OID 0)
-- Dependencies: 1955
-- Name: scriptsdir; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE scriptsdir FROM PUBLIC;
REVOKE ALL ON TABLE scriptsdir FROM postgres;
GRANT ALL ON TABLE scriptsdir TO postgres;
GRANT ALL ON TABLE scriptsdir TO dps;


--
-- TOC entry 2981 (class 0 OID 0)
-- Dependencies: 1956
-- Name: scriptsgroups; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE scriptsgroups FROM PUBLIC;
REVOKE ALL ON TABLE scriptsgroups FROM postgres;
GRANT ALL ON TABLE scriptsgroups TO postgres;
GRANT ALL ON TABLE scriptsgroups TO dps;


--
-- TOC entry 2982 (class 0 OID 0)
-- Dependencies: 1957
-- Name: scriptsusers; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE scriptsusers FROM PUBLIC;
REVOKE ALL ON TABLE scriptsusers FROM postgres;
GRANT ALL ON TABLE scriptsusers TO postgres;
GRANT ALL ON TABLE scriptsusers TO dps;


--
-- TOC entry 2983 (class 0 OID 0)
-- Dependencies: 1958
-- Name: sessions; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE sessions FROM PUBLIC;
REVOKE ALL ON TABLE sessions FROM postgres;
GRANT ALL ON TABLE sessions TO postgres;
GRANT ALL ON TABLE sessions TO dps;


--
-- TOC entry 2984 (class 0 OID 0)
-- Dependencies: 1959
-- Name: sessionvalues; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE sessionvalues FROM PUBLIC;
REVOKE ALL ON TABLE sessionvalues FROM postgres;
GRANT ALL ON TABLE sessionvalues TO postgres;
GRANT ALL ON TABLE sessionvalues TO dps;


--
-- TOC entry 2985 (class 0 OID 0)
-- Dependencies: 1960
-- Name: showitems; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE showitems FROM PUBLIC;
REVOKE ALL ON TABLE showitems FROM postgres;
GRANT ALL ON TABLE showitems TO postgres;
GRANT ALL ON TABLE showitems TO dps;


--
-- TOC entry 2986 (class 0 OID 0)
-- Dependencies: 1961
-- Name: showplandir; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE showplandir FROM PUBLIC;
REVOKE ALL ON TABLE showplandir FROM postgres;
GRANT ALL ON TABLE showplandir TO postgres;
GRANT ALL ON TABLE showplandir TO dps;


--
-- TOC entry 2987 (class 0 OID 0)
-- Dependencies: 1962
-- Name: showplangroups; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE showplangroups FROM PUBLIC;
REVOKE ALL ON TABLE showplangroups FROM postgres;
GRANT ALL ON TABLE showplangroups TO postgres;
GRANT ALL ON TABLE showplangroups TO dps;


--
-- TOC entry 2988 (class 0 OID 0)
-- Dependencies: 1963
-- Name: showplans; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE showplans FROM PUBLIC;
REVOKE ALL ON TABLE showplans FROM postgres;
GRANT ALL ON TABLE showplans TO postgres;
GRANT ALL ON TABLE showplans TO dps;


--
-- TOC entry 2989 (class 0 OID 0)
-- Dependencies: 1964
-- Name: showplansdir; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE showplansdir FROM PUBLIC;
REVOKE ALL ON TABLE showplansdir FROM postgres;
GRANT ALL ON TABLE showplansdir TO postgres;
GRANT ALL ON TABLE showplansdir TO dps;


--
-- TOC entry 2990 (class 0 OID 0)
-- Dependencies: 1965
-- Name: showplansgroups; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE showplansgroups FROM PUBLIC;
REVOKE ALL ON TABLE showplansgroups FROM postgres;
GRANT ALL ON TABLE showplansgroups TO postgres;
GRANT ALL ON TABLE showplansgroups TO dps;


--
-- TOC entry 2991 (class 0 OID 0)
-- Dependencies: 1966
-- Name: showplansusers; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE showplansusers FROM PUBLIC;
REVOKE ALL ON TABLE showplansusers FROM postgres;
GRANT ALL ON TABLE showplansusers TO postgres;
GRANT ALL ON TABLE showplansusers TO dps;


--
-- TOC entry 2992 (class 0 OID 0)
-- Dependencies: 1967
-- Name: showplanusers; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE showplanusers FROM PUBLIC;
REVOKE ALL ON TABLE showplanusers FROM postgres;
GRANT ALL ON TABLE showplanusers TO postgres;
GRANT ALL ON TABLE showplanusers TO dps;


--
-- TOC entry 2993 (class 0 OID 0)
-- Dependencies: 1968
-- Name: sustschedule; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE sustschedule FROM PUBLIC;
REVOKE ALL ON TABLE sustschedule FROM postgres;
GRANT ALL ON TABLE sustschedule TO postgres;
GRANT ALL ON TABLE sustschedule TO dps;


--
-- TOC entry 2994 (class 0 OID 0)
-- Dependencies: 1969
-- Name: tasks; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE tasks FROM PUBLIC;
REVOKE ALL ON TABLE tasks FROM postgres;
GRANT ALL ON TABLE tasks TO postgres;
GRANT ALL ON TABLE tasks TO dps;


--
-- TOC entry 2995 (class 0 OID 0)
-- Dependencies: 1970
-- Name: taskschedule; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE taskschedule FROM PUBLIC;
REVOKE ALL ON TABLE taskschedule FROM postgres;
GRANT ALL ON TABLE taskschedule TO postgres;
GRANT ALL ON TABLE taskschedule TO dps;


--
-- TOC entry 2996 (class 0 OID 0)
-- Dependencies: 1971
-- Name: templates; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE templates FROM PUBLIC;
REVOKE ALL ON TABLE templates FROM postgres;
GRANT ALL ON TABLE templates TO postgres;
GRANT ALL ON TABLE templates TO dps;


--
-- TOC entry 2997 (class 0 OID 0)
-- Dependencies: 1972
-- Name: txcategories; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE txcategories FROM PUBLIC;
REVOKE ALL ON TABLE txcategories FROM postgres;
GRANT ALL ON TABLE txcategories TO postgres;
GRANT ALL ON TABLE txcategories TO dps;


--
-- TOC entry 2998 (class 0 OID 0)
-- Dependencies: 1973
-- Name: txschedule; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE txschedule FROM PUBLIC;
REVOKE ALL ON TABLE txschedule FROM postgres;
GRANT ALL ON TABLE txschedule TO postgres;
GRANT ALL ON TABLE txschedule TO dps;


--
-- TOC entry 2999 (class 0 OID 0)
-- Dependencies: 1974
-- Name: txshows; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE txshows FROM PUBLIC;
REVOKE ALL ON TABLE txshows FROM postgres;
GRANT ALL ON TABLE txshows TO postgres;
GRANT ALL ON TABLE txshows TO dps;


--
-- TOC entry 3000 (class 0 OID 0)
-- Dependencies: 1975
-- Name: txshowskeywords; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE txshowskeywords FROM PUBLIC;
REVOKE ALL ON TABLE txshowskeywords FROM postgres;
GRANT ALL ON TABLE txshowskeywords TO postgres;
GRANT ALL ON TABLE txshowskeywords TO dps;


--
-- TOC entry 3001 (class 0 OID 0)
-- Dependencies: 1976
-- Name: txshowsusers; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE txshowsusers FROM PUBLIC;
REVOKE ALL ON TABLE txshowsusers FROM postgres;
GRANT ALL ON TABLE txshowsusers TO postgres;
GRANT ALL ON TABLE txshowsusers TO dps;


--
-- TOC entry 3002 (class 0 OID 0)
-- Dependencies: 1977
-- Name: users; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE users FROM PUBLIC;
REVOKE ALL ON TABLE users FROM postgres;
GRANT ALL ON TABLE users TO postgres;
GRANT ALL ON TABLE users TO dps;


--
-- TOC entry 3003 (class 0 OID 0)
-- Dependencies: 1978
-- Name: usersconfigs; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE usersconfigs FROM PUBLIC;
REVOKE ALL ON TABLE usersconfigs FROM postgres;
GRANT ALL ON TABLE usersconfigs TO postgres;
GRANT ALL ON TABLE usersconfigs TO dps;


--
-- TOC entry 3004 (class 0 OID 0)
-- Dependencies: 1979
-- Name: usersgroups; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE usersgroups FROM PUBLIC;
REVOKE ALL ON TABLE usersgroups FROM postgres;
GRANT ALL ON TABLE usersgroups TO postgres;
GRANT ALL ON TABLE usersgroups TO dps;


--
-- TOC entry 3005 (class 0 OID 0)
-- Dependencies: 1980
-- Name: v_audio_adverts; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_audio_adverts FROM PUBLIC;
REVOKE ALL ON TABLE v_audio_adverts FROM postgres;
GRANT ALL ON TABLE v_audio_adverts TO postgres;


--
-- TOC entry 3006 (class 0 OID 0)
-- Dependencies: 1981
-- Name: v_audio_jingles; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_audio_jingles FROM PUBLIC;
REVOKE ALL ON TABLE v_audio_jingles FROM postgres;
GRANT ALL ON TABLE v_audio_jingles TO postgres;


--
-- TOC entry 3007 (class 0 OID 0)
-- Dependencies: 1982
-- Name: v_audio_music; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_audio_music FROM PUBLIC;
REVOKE ALL ON TABLE v_audio_music FROM postgres;
GRANT ALL ON TABLE v_audio_music TO postgres;


--
-- TOC entry 3008 (class 0 OID 0)
-- Dependencies: 1983
-- Name: v_audio_prerec; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_audio_prerec FROM PUBLIC;
REVOKE ALL ON TABLE v_audio_prerec FROM postgres;
GRANT ALL ON TABLE v_audio_prerec TO postgres;


--
-- TOC entry 3009 (class 0 OID 0)
-- Dependencies: 1984
-- Name: v_audio; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_audio FROM PUBLIC;
REVOKE ALL ON TABLE v_audio FROM postgres;
GRANT ALL ON TABLE v_audio TO postgres;


--
-- TOC entry 3010 (class 0 OID 0)
-- Dependencies: 1985
-- Name: v_audiowalls; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_audiowalls FROM PUBLIC;
REVOKE ALL ON TABLE v_audiowalls FROM postgres;
GRANT ALL ON TABLE v_audiowalls TO postgres;


--
-- TOC entry 3011 (class 0 OID 0)
-- Dependencies: 1986
-- Name: v_cartwalls; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_cartwalls FROM PUBLIC;
REVOKE ALL ON TABLE v_cartwalls FROM postgres;
GRANT ALL ON TABLE v_cartwalls TO postgres;


--
-- TOC entry 3012 (class 0 OID 0)
-- Dependencies: 1987
-- Name: v_playlists; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_playlists FROM PUBLIC;
REVOKE ALL ON TABLE v_playlists FROM postgres;
GRANT ALL ON TABLE v_playlists TO postgres;


--
-- TOC entry 3013 (class 0 OID 0)
-- Dependencies: 1988
-- Name: v_scripts; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_scripts FROM PUBLIC;
REVOKE ALL ON TABLE v_scripts FROM postgres;
GRANT ALL ON TABLE v_scripts TO postgres;


--
-- TOC entry 3014 (class 0 OID 0)
-- Dependencies: 1989
-- Name: v_showplan; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_showplan FROM PUBLIC;
REVOKE ALL ON TABLE v_showplan FROM postgres;
GRANT ALL ON TABLE v_showplan TO postgres;


--
-- TOC entry 3015 (class 0 OID 0)
-- Dependencies: 1990
-- Name: v_tree_advert_explicit; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_advert_explicit FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_advert_explicit FROM postgres;
GRANT ALL ON TABLE v_tree_advert_explicit TO postgres;


--
-- TOC entry 3016 (class 0 OID 0)
-- Dependencies: 1991
-- Name: v_tree_advert_inherited; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_advert_inherited FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_advert_inherited FROM postgres;
GRANT ALL ON TABLE v_tree_advert_inherited TO postgres;


--
-- TOC entry 3017 (class 0 OID 0)
-- Dependencies: 1992
-- Name: v_tree_advert; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_advert FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_advert FROM postgres;
GRANT ALL ON TABLE v_tree_advert TO postgres;


--
-- TOC entry 3018 (class 0 OID 0)
-- Dependencies: 1993
-- Name: v_tree_aw_sets_explicit; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_aw_sets_explicit FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_aw_sets_explicit FROM postgres;
GRANT ALL ON TABLE v_tree_aw_sets_explicit TO postgres;


--
-- TOC entry 3019 (class 0 OID 0)
-- Dependencies: 1994
-- Name: v_tree_aw_sets_inherited; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_aw_sets_inherited FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_aw_sets_inherited FROM postgres;
GRANT ALL ON TABLE v_tree_aw_sets_inherited TO postgres;


--
-- TOC entry 3020 (class 0 OID 0)
-- Dependencies: 1995
-- Name: v_tree_aw_sets; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_aw_sets FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_aw_sets FROM postgres;
GRANT ALL ON TABLE v_tree_aw_sets TO postgres;


--
-- TOC entry 3021 (class 0 OID 0)
-- Dependencies: 1996
-- Name: v_tree_dir_explicit; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_dir_explicit FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_dir_explicit FROM postgres;
GRANT ALL ON TABLE v_tree_dir_explicit TO postgres;


--
-- TOC entry 3022 (class 0 OID 0)
-- Dependencies: 1997
-- Name: v_tree_dir_inherited; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_dir_inherited FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_dir_inherited FROM postgres;
GRANT ALL ON TABLE v_tree_dir_inherited TO postgres;


--
-- TOC entry 3023 (class 0 OID 0)
-- Dependencies: 1998
-- Name: v_tree_dir; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_dir FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_dir FROM postgres;
GRANT ALL ON TABLE v_tree_dir TO postgres;


--
-- TOC entry 3024 (class 0 OID 0)
-- Dependencies: 1999
-- Name: v_tree_jingle_explicit; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_jingle_explicit FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_jingle_explicit FROM postgres;
GRANT ALL ON TABLE v_tree_jingle_explicit TO postgres;


--
-- TOC entry 3025 (class 0 OID 0)
-- Dependencies: 2000
-- Name: v_tree_jingle_inherited; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_jingle_inherited FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_jingle_inherited FROM postgres;
GRANT ALL ON TABLE v_tree_jingle_inherited TO postgres;


--
-- TOC entry 3026 (class 0 OID 0)
-- Dependencies: 2001
-- Name: v_tree_jingle; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_jingle FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_jingle FROM postgres;
GRANT ALL ON TABLE v_tree_jingle TO postgres;


--
-- TOC entry 3027 (class 0 OID 0)
-- Dependencies: 2002
-- Name: v_tree_music_explicit; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_music_explicit FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_music_explicit FROM postgres;
GRANT ALL ON TABLE v_tree_music_explicit TO postgres;


--
-- TOC entry 3028 (class 0 OID 0)
-- Dependencies: 2003
-- Name: v_tree_music_inherited; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_music_inherited FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_music_inherited FROM postgres;
GRANT ALL ON TABLE v_tree_music_inherited TO postgres;


--
-- TOC entry 3029 (class 0 OID 0)
-- Dependencies: 2004
-- Name: v_tree_music; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_music FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_music FROM postgres;
GRANT ALL ON TABLE v_tree_music TO postgres;


--
-- TOC entry 3030 (class 0 OID 0)
-- Dependencies: 2005
-- Name: v_tree_prerec_explicit; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_prerec_explicit FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_prerec_explicit FROM postgres;
GRANT ALL ON TABLE v_tree_prerec_explicit TO postgres;


--
-- TOC entry 3031 (class 0 OID 0)
-- Dependencies: 2006
-- Name: v_tree_prerec_inherited; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_prerec_inherited FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_prerec_inherited FROM postgres;
GRANT ALL ON TABLE v_tree_prerec_inherited TO postgres;


--
-- TOC entry 3032 (class 0 OID 0)
-- Dependencies: 2007
-- Name: v_tree_prerec; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_prerec FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_prerec FROM postgres;
GRANT ALL ON TABLE v_tree_prerec TO postgres;


--
-- TOC entry 3033 (class 0 OID 0)
-- Dependencies: 2008
-- Name: v_tree_script_explicit; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_script_explicit FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_script_explicit FROM postgres;
GRANT ALL ON TABLE v_tree_script_explicit TO postgres;


--
-- TOC entry 3034 (class 0 OID 0)
-- Dependencies: 2009
-- Name: v_tree_script_inherited; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_script_inherited FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_script_inherited FROM postgres;
GRANT ALL ON TABLE v_tree_script_inherited TO postgres;


--
-- TOC entry 3035 (class 0 OID 0)
-- Dependencies: 2010
-- Name: v_tree_script; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_script FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_script FROM postgres;
GRANT ALL ON TABLE v_tree_script TO postgres;


--
-- TOC entry 3036 (class 0 OID 0)
-- Dependencies: 2011
-- Name: v_tree_showplan_explicit; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_showplan_explicit FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_showplan_explicit FROM postgres;
GRANT ALL ON TABLE v_tree_showplan_explicit TO postgres;


--
-- TOC entry 3037 (class 0 OID 0)
-- Dependencies: 2012
-- Name: v_tree_showplan_inherited; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_showplan_inherited FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_showplan_inherited FROM postgres;
GRANT ALL ON TABLE v_tree_showplan_inherited TO postgres;


--
-- TOC entry 3038 (class 0 OID 0)
-- Dependencies: 2013
-- Name: v_tree_showplan; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_showplan FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_showplan FROM postgres;
GRANT ALL ON TABLE v_tree_showplan TO postgres;


--
-- TOC entry 3039 (class 0 OID 0)
-- Dependencies: 2014
-- Name: v_tree; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree FROM PUBLIC;
REVOKE ALL ON TABLE v_tree FROM postgres;
GRANT ALL ON TABLE v_tree TO postgres;


--
-- TOC entry 3040 (class 0 OID 0)
-- Dependencies: 2015
-- Name: v_tree_audio; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_audio FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_audio FROM postgres;
GRANT ALL ON TABLE v_tree_audio TO postgres;


--
-- TOC entry 3041 (class 0 OID 0)
-- Dependencies: 2016
-- Name: v_tree_cartset_explicit; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_cartset_explicit FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_cartset_explicit FROM postgres;
GRANT ALL ON TABLE v_tree_cartset_explicit TO postgres;


--
-- TOC entry 3042 (class 0 OID 0)
-- Dependencies: 2017
-- Name: v_tree_cartset_inherited; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_cartset_inherited FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_cartset_inherited FROM postgres;
GRANT ALL ON TABLE v_tree_cartset_inherited TO postgres;


--
-- TOC entry 3043 (class 0 OID 0)
-- Dependencies: 2018
-- Name: v_tree_cartset; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE v_tree_cartset FROM PUBLIC;
REVOKE ALL ON TABLE v_tree_cartset FROM postgres;
GRANT ALL ON TABLE v_tree_cartset TO postgres;


--
-- TOC entry 3045 (class 0 OID 0)
-- Dependencies: 2019
-- Name: advertschedule_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE advertschedule_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE advertschedule_id_seq FROM postgres;
GRANT ALL ON SEQUENCE advertschedule_id_seq TO postgres;


--
-- TOC entry 3047 (class 0 OID 0)
-- Dependencies: 2020
-- Name: albums_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE albums_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE albums_id_seq FROM postgres;
GRANT ALL ON SEQUENCE albums_id_seq TO postgres;


--
-- TOC entry 3049 (class 0 OID 0)
-- Dependencies: 2021
-- Name: archives_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE archives_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE archives_id_seq FROM postgres;
GRANT ALL ON SEQUENCE archives_id_seq TO postgres;


--
-- TOC entry 3051 (class 0 OID 0)
-- Dependencies: 2022
-- Name: artists_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE artists_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE artists_id_seq FROM postgres;
GRANT ALL ON SEQUENCE artists_id_seq TO postgres;


--
-- TOC entry 3053 (class 0 OID 0)
-- Dependencies: 2023
-- Name: artistskeywords_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE artistskeywords_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE artistskeywords_id_seq FROM postgres;
GRANT ALL ON SEQUENCE artistskeywords_id_seq TO postgres;


--
-- TOC entry 3055 (class 0 OID 0)
-- Dependencies: 2024
-- Name: audio_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE audio_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE audio_id_seq FROM postgres;
GRANT ALL ON SEQUENCE audio_id_seq TO postgres;


--
-- TOC entry 3057 (class 0 OID 0)
-- Dependencies: 2025
-- Name: audioartists_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE audioartists_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE audioartists_id_seq FROM postgres;
GRANT ALL ON SEQUENCE audioartists_id_seq TO postgres;


--
-- TOC entry 3059 (class 0 OID 0)
-- Dependencies: 2026
-- Name: audiocomments_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE audiocomments_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE audiocomments_id_seq FROM postgres;
GRANT ALL ON SEQUENCE audiocomments_id_seq TO postgres;


--
-- TOC entry 3061 (class 0 OID 0)
-- Dependencies: 2027
-- Name: audiodir_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE audiodir_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE audiodir_id_seq FROM postgres;
GRANT ALL ON SEQUENCE audiodir_id_seq TO postgres;


--
-- TOC entry 3063 (class 0 OID 0)
-- Dependencies: 2028
-- Name: audioext_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE audioext_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE audioext_id_seq FROM postgres;
GRANT ALL ON SEQUENCE audioext_id_seq TO postgres;


--
-- TOC entry 3065 (class 0 OID 0)
-- Dependencies: 2029
-- Name: audiogroups_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE audiogroups_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE audiogroups_id_seq FROM postgres;
GRANT ALL ON SEQUENCE audiogroups_id_seq TO postgres;


--
-- TOC entry 3067 (class 0 OID 0)
-- Dependencies: 2030
-- Name: audiojinglepkgs_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE audiojinglepkgs_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE audiojinglepkgs_id_seq FROM postgres;
GRANT ALL ON SEQUENCE audiojinglepkgs_id_seq TO postgres;


--
-- TOC entry 3069 (class 0 OID 0)
-- Dependencies: 2031
-- Name: audiokeywords_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE audiokeywords_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE audiokeywords_id_seq FROM postgres;
GRANT ALL ON SEQUENCE audiokeywords_id_seq TO postgres;


--
-- TOC entry 3071 (class 0 OID 0)
-- Dependencies: 2032
-- Name: audiolog_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE audiolog_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE audiolog_id_seq FROM postgres;
GRANT ALL ON SEQUENCE audiolog_id_seq TO postgres;


--
-- TOC entry 3073 (class 0 OID 0)
-- Dependencies: 2033
-- Name: audioplaylists_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE audioplaylists_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE audioplaylists_id_seq FROM postgres;
GRANT ALL ON SEQUENCE audioplaylists_id_seq TO postgres;


--
-- TOC entry 3075 (class 0 OID 0)
-- Dependencies: 2034
-- Name: audiotypes_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE audiotypes_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE audiotypes_id_seq FROM postgres;
GRANT ALL ON SEQUENCE audiotypes_id_seq TO postgres;


--
-- TOC entry 3077 (class 0 OID 0)
-- Dependencies: 2035
-- Name: audiousers_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE audiousers_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE audiousers_id_seq FROM postgres;
GRANT ALL ON SEQUENCE audiousers_id_seq TO postgres;


--
-- TOC entry 3079 (class 0 OID 0)
-- Dependencies: 2036
-- Name: aw_items_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE aw_items_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE aw_items_id_seq FROM postgres;
GRANT ALL ON SEQUENCE aw_items_id_seq TO postgres;


--
-- TOC entry 3081 (class 0 OID 0)
-- Dependencies: 2037
-- Name: aw_props_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE aw_props_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE aw_props_id_seq FROM postgres;
GRANT ALL ON SEQUENCE aw_props_id_seq TO postgres;


--
-- TOC entry 3083 (class 0 OID 0)
-- Dependencies: 2038
-- Name: aw_sets_dir_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE aw_sets_dir_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE aw_sets_dir_id_seq FROM postgres;
GRANT ALL ON SEQUENCE aw_sets_dir_id_seq TO postgres;


--
-- TOC entry 3085 (class 0 OID 0)
-- Dependencies: 2039
-- Name: aw_sets_groups_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE aw_sets_groups_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE aw_sets_groups_id_seq FROM postgres;
GRANT ALL ON SEQUENCE aw_sets_groups_id_seq TO postgres;


--
-- TOC entry 3087 (class 0 OID 0)
-- Dependencies: 2040
-- Name: aw_sets_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE aw_sets_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE aw_sets_id_seq FROM postgres;
GRANT ALL ON SEQUENCE aw_sets_id_seq TO postgres;


--
-- TOC entry 3089 (class 0 OID 0)
-- Dependencies: 2041
-- Name: aw_sets_users_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE aw_sets_users_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE aw_sets_users_id_seq FROM postgres;
GRANT ALL ON SEQUENCE aw_sets_users_id_seq TO postgres;


--
-- TOC entry 3091 (class 0 OID 0)
-- Dependencies: 2042
-- Name: aw_styles_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE aw_styles_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE aw_styles_id_seq FROM postgres;
GRANT ALL ON SEQUENCE aw_styles_id_seq TO postgres;


--
-- TOC entry 3093 (class 0 OID 0)
-- Dependencies: 2043
-- Name: aw_styles_props_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE aw_styles_props_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE aw_styles_props_id_seq FROM postgres;
GRANT ALL ON SEQUENCE aw_styles_props_id_seq TO postgres;


--
-- TOC entry 3095 (class 0 OID 0)
-- Dependencies: 2044
-- Name: aw_walls_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE aw_walls_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE aw_walls_id_seq FROM postgres;
GRANT ALL ON SEQUENCE aw_walls_id_seq TO postgres;


--
-- TOC entry 3097 (class 0 OID 0)
-- Dependencies: 2045
-- Name: bins_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE bins_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE bins_id_seq FROM postgres;
GRANT ALL ON SEQUENCE bins_id_seq TO postgres;


--
-- TOC entry 3099 (class 0 OID 0)
-- Dependencies: 2046
-- Name: binsartists_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE binsartists_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE binsartists_id_seq FROM postgres;
GRANT ALL ON SEQUENCE binsartists_id_seq TO postgres;


--
-- TOC entry 3101 (class 0 OID 0)
-- Dependencies: 2047
-- Name: binsaudio_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE binsaudio_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE binsaudio_id_seq FROM postgres;
GRANT ALL ON SEQUENCE binsaudio_id_seq TO postgres;


--
-- TOC entry 3103 (class 0 OID 0)
-- Dependencies: 2048
-- Name: binskeywords_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE binskeywords_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE binskeywords_id_seq FROM postgres;
GRANT ALL ON SEQUENCE binskeywords_id_seq TO postgres;


--
-- TOC entry 3105 (class 0 OID 0)
-- Dependencies: 2049
-- Name: binsschedule_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE binsschedule_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE binsschedule_id_seq FROM postgres;
GRANT ALL ON SEQUENCE binsschedule_id_seq TO postgres;


--
-- TOC entry 3107 (class 0 OID 0)
-- Dependencies: 2050
-- Name: cartproperties_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE cartproperties_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE cartproperties_id_seq FROM postgres;
GRANT ALL ON SEQUENCE cartproperties_id_seq TO postgres;


--
-- TOC entry 3109 (class 0 OID 0)
-- Dependencies: 2051
-- Name: cartsaudio_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE cartsaudio_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE cartsaudio_id_seq FROM postgres;
GRANT ALL ON SEQUENCE cartsaudio_id_seq TO postgres;


--
-- TOC entry 3111 (class 0 OID 0)
-- Dependencies: 2052
-- Name: cartsets_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE cartsets_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE cartsets_id_seq FROM postgres;
GRANT ALL ON SEQUENCE cartsets_id_seq TO postgres;


--
-- TOC entry 3113 (class 0 OID 0)
-- Dependencies: 2053
-- Name: cartsetsdir_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE cartsetsdir_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE cartsetsdir_id_seq FROM postgres;
GRANT ALL ON SEQUENCE cartsetsdir_id_seq TO postgres;


--
-- TOC entry 3115 (class 0 OID 0)
-- Dependencies: 2054
-- Name: cartsetsgroups_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE cartsetsgroups_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE cartsetsgroups_id_seq FROM postgres;
GRANT ALL ON SEQUENCE cartsetsgroups_id_seq TO postgres;


--
-- TOC entry 3117 (class 0 OID 0)
-- Dependencies: 2055
-- Name: cartsetsusers_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE cartsetsusers_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE cartsetsusers_id_seq FROM postgres;
GRANT ALL ON SEQUENCE cartsetsusers_id_seq TO postgres;


--
-- TOC entry 3119 (class 0 OID 0)
-- Dependencies: 2056
-- Name: cartstyleprops_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE cartstyleprops_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE cartstyleprops_id_seq FROM postgres;
GRANT ALL ON SEQUENCE cartstyleprops_id_seq TO postgres;


--
-- TOC entry 3121 (class 0 OID 0)
-- Dependencies: 2057
-- Name: cartstyles_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE cartstyles_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE cartstyles_id_seq FROM postgres;
GRANT ALL ON SEQUENCE cartstyles_id_seq TO postgres;


--
-- TOC entry 3123 (class 0 OID 0)
-- Dependencies: 2058
-- Name: cartwalls_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE cartwalls_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE cartwalls_id_seq FROM postgres;
GRANT ALL ON SEQUENCE cartwalls_id_seq TO postgres;


--
-- TOC entry 3125 (class 0 OID 0)
-- Dependencies: 2059
-- Name: changelog_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE changelog_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE changelog_id_seq FROM postgres;
GRANT ALL ON SEQUENCE changelog_id_seq TO postgres;


--
-- TOC entry 3127 (class 0 OID 0)
-- Dependencies: 2060
-- Name: cmscontent_contentid_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE cmscontent_contentid_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE cmscontent_contentid_seq FROM postgres;
GRANT ALL ON SEQUENCE cmscontent_contentid_seq TO postgres;


--
-- TOC entry 3129 (class 0 OID 0)
-- Dependencies: 2061
-- Name: cmsregions_regionid_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE cmsregions_regionid_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE cmsregions_regionid_seq FROM postgres;
GRANT ALL ON SEQUENCE cmsregions_regionid_seq TO postgres;


--
-- TOC entry 3131 (class 0 OID 0)
-- Dependencies: 2062
-- Name: companies_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE companies_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE companies_id_seq FROM postgres;
GRANT ALL ON SEQUENCE companies_id_seq TO postgres;


--
-- TOC entry 3133 (class 0 OID 0)
-- Dependencies: 2063
-- Name: configs_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE configs_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE configs_id_seq FROM postgres;
GRANT ALL ON SEQUENCE configs_id_seq TO postgres;


--
-- TOC entry 3135 (class 0 OID 0)
-- Dependencies: 2064
-- Name: configuration_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE configuration_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE configuration_id_seq FROM postgres;
GRANT ALL ON SEQUENCE configuration_id_seq TO postgres;


--
-- TOC entry 3137 (class 0 OID 0)
-- Dependencies: 2065
-- Name: dir_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE dir_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE dir_id_seq FROM postgres;
GRANT ALL ON SEQUENCE dir_id_seq TO postgres;


--
-- TOC entry 3139 (class 0 OID 0)
-- Dependencies: 2066
-- Name: dirgroups_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE dirgroups_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE dirgroups_id_seq FROM postgres;
GRANT ALL ON SEQUENCE dirgroups_id_seq TO postgres;


--
-- TOC entry 3141 (class 0 OID 0)
-- Dependencies: 2067
-- Name: dirusers_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE dirusers_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE dirusers_id_seq FROM postgres;
GRANT ALL ON SEQUENCE dirusers_id_seq TO postgres;


--
-- TOC entry 3143 (class 0 OID 0)
-- Dependencies: 2068
-- Name: email_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE email_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE email_id_seq FROM postgres;
GRANT ALL ON SEQUENCE email_id_seq TO postgres;


--
-- TOC entry 3145 (class 0 OID 0)
-- Dependencies: 2069
-- Name: extfeeds_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE extfeeds_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE extfeeds_id_seq FROM postgres;
GRANT ALL ON SEQUENCE extfeeds_id_seq TO postgres;


--
-- TOC entry 3147 (class 0 OID 0)
-- Dependencies: 2070
-- Name: fieldvalidators_ruleid_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE fieldvalidators_ruleid_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE fieldvalidators_ruleid_seq FROM postgres;
GRANT ALL ON SEQUENCE fieldvalidators_ruleid_seq TO postgres;


--
-- TOC entry 3149 (class 0 OID 0)
-- Dependencies: 2071
-- Name: formfields_fieldid_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE formfields_fieldid_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE formfields_fieldid_seq FROM postgres;
GRANT ALL ON SEQUENCE formfields_fieldid_seq TO postgres;


--
-- TOC entry 3151 (class 0 OID 0)
-- Dependencies: 2072
-- Name: forms_formid_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE forms_formid_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE forms_formid_seq FROM postgres;
GRANT ALL ON SEQUENCE forms_formid_seq TO postgres;


--
-- TOC entry 3153 (class 0 OID 0)
-- Dependencies: 2073
-- Name: groups_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE groups_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE groups_id_seq FROM postgres;
GRANT ALL ON SEQUENCE groups_id_seq TO postgres;


--
-- TOC entry 3155 (class 0 OID 0)
-- Dependencies: 2074
-- Name: jinglepkgs_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE jinglepkgs_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE jinglepkgs_id_seq FROM postgres;
GRANT ALL ON SEQUENCE jinglepkgs_id_seq TO postgres;


--
-- TOC entry 3157 (class 0 OID 0)
-- Dependencies: 2075
-- Name: jingletypes_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE jingletypes_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE jingletypes_id_seq FROM postgres;
GRANT ALL ON SEQUENCE jingletypes_id_seq TO postgres;


--
-- TOC entry 3159 (class 0 OID 0)
-- Dependencies: 2076
-- Name: keywords_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE keywords_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE keywords_id_seq FROM postgres;
GRANT ALL ON SEQUENCE keywords_id_seq TO postgres;


--
-- TOC entry 3161 (class 0 OID 0)
-- Dependencies: 2077
-- Name: lifespans_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE lifespans_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE lifespans_id_seq FROM postgres;
GRANT ALL ON SEQUENCE lifespans_id_seq TO postgres;


--
-- TOC entry 3163 (class 0 OID 0)
-- Dependencies: 2078
-- Name: log_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE log_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE log_id_seq FROM postgres;
GRANT ALL ON SEQUENCE log_id_seq TO postgres;


--
-- TOC entry 3165 (class 0 OID 0)
-- Dependencies: 2079
-- Name: logentries_entryid_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE logentries_entryid_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE logentries_entryid_seq FROM postgres;
GRANT ALL ON SEQUENCE logentries_entryid_seq TO postgres;


--
-- TOC entry 3168 (class 0 OID 0)
-- Dependencies: 2081
-- Name: patches_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE patches_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE patches_id_seq FROM postgres;
GRANT ALL ON SEQUENCE patches_id_seq TO postgres;


--
-- TOC entry 3170 (class 0 OID 0)
-- Dependencies: 2082
-- Name: playlists_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE playlists_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE playlists_id_seq FROM postgres;
GRANT ALL ON SEQUENCE playlists_id_seq TO postgres;


--
-- TOC entry 3172 (class 0 OID 0)
-- Dependencies: 2083
-- Name: realms_realmid_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE realms_realmid_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE realms_realmid_seq FROM postgres;
GRANT ALL ON SEQUENCE realms_realmid_seq TO postgres;


--
-- TOC entry 3174 (class 0 OID 0)
-- Dependencies: 2084
-- Name: realmuserlink_userid_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE realmuserlink_userid_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE realmuserlink_userid_seq FROM postgres;
GRANT ALL ON SEQUENCE realmuserlink_userid_seq TO postgres;


--
-- TOC entry 3176 (class 0 OID 0)
-- Dependencies: 2085
-- Name: requests_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE requests_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE requests_id_seq FROM postgres;
GRANT ALL ON SEQUENCE requests_id_seq TO postgres;


--
-- TOC entry 3178 (class 0 OID 0)
-- Dependencies: 2086
-- Name: scripts_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE scripts_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE scripts_id_seq FROM postgres;
GRANT ALL ON SEQUENCE scripts_id_seq TO postgres;


--
-- TOC entry 3180 (class 0 OID 0)
-- Dependencies: 2087
-- Name: scriptsdir_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE scriptsdir_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE scriptsdir_id_seq FROM postgres;
GRANT ALL ON SEQUENCE scriptsdir_id_seq TO postgres;


--
-- TOC entry 3182 (class 0 OID 0)
-- Dependencies: 2088
-- Name: scriptsgroups_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE scriptsgroups_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE scriptsgroups_id_seq FROM postgres;
GRANT ALL ON SEQUENCE scriptsgroups_id_seq TO postgres;


--
-- TOC entry 3184 (class 0 OID 0)
-- Dependencies: 2089
-- Name: scriptsusers_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE scriptsusers_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE scriptsusers_id_seq FROM postgres;
GRANT ALL ON SEQUENCE scriptsusers_id_seq TO postgres;


--
-- TOC entry 3186 (class 0 OID 0)
-- Dependencies: 2091
-- Name: sessions_sessionid_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE sessions_sessionid_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE sessions_sessionid_seq FROM postgres;
GRANT ALL ON SEQUENCE sessions_sessionid_seq TO postgres;


--
-- TOC entry 3188 (class 0 OID 0)
-- Dependencies: 2093
-- Name: sessionvalues_valueid_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE sessionvalues_valueid_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE sessionvalues_valueid_seq FROM postgres;
GRANT ALL ON SEQUENCE sessionvalues_valueid_seq TO postgres;


--
-- TOC entry 3190 (class 0 OID 0)
-- Dependencies: 2094
-- Name: showitems_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE showitems_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE showitems_id_seq FROM postgres;
GRANT ALL ON SEQUENCE showitems_id_seq TO postgres;


--
-- TOC entry 3192 (class 0 OID 0)
-- Dependencies: 2095
-- Name: showplandir_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE showplandir_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE showplandir_id_seq FROM postgres;
GRANT ALL ON SEQUENCE showplandir_id_seq TO postgres;


--
-- TOC entry 3194 (class 0 OID 0)
-- Dependencies: 2096
-- Name: showplangroups_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE showplangroups_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE showplangroups_id_seq FROM postgres;
GRANT ALL ON SEQUENCE showplangroups_id_seq TO postgres;


--
-- TOC entry 3196 (class 0 OID 0)
-- Dependencies: 2097
-- Name: showplans_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE showplans_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE showplans_id_seq FROM postgres;
GRANT ALL ON SEQUENCE showplans_id_seq TO postgres;


--
-- TOC entry 3198 (class 0 OID 0)
-- Dependencies: 2098
-- Name: showplansdir_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE showplansdir_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE showplansdir_id_seq FROM postgres;
GRANT ALL ON SEQUENCE showplansdir_id_seq TO postgres;


--
-- TOC entry 3200 (class 0 OID 0)
-- Dependencies: 2099
-- Name: showplansgroups_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE showplansgroups_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE showplansgroups_id_seq FROM postgres;
GRANT ALL ON SEQUENCE showplansgroups_id_seq TO postgres;


--
-- TOC entry 3202 (class 0 OID 0)
-- Dependencies: 2100
-- Name: showplansusers_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE showplansusers_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE showplansusers_id_seq FROM postgres;
GRANT ALL ON SEQUENCE showplansusers_id_seq TO postgres;


--
-- TOC entry 3204 (class 0 OID 0)
-- Dependencies: 2101
-- Name: showplanusers_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE showplanusers_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE showplanusers_id_seq FROM postgres;
GRANT ALL ON SEQUENCE showplanusers_id_seq TO postgres;


--
-- TOC entry 3206 (class 0 OID 0)
-- Dependencies: 2102
-- Name: sustschedule_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE sustschedule_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE sustschedule_id_seq FROM postgres;
GRANT ALL ON SEQUENCE sustschedule_id_seq TO postgres;


--
-- TOC entry 3208 (class 0 OID 0)
-- Dependencies: 2103
-- Name: tasks_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE tasks_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE tasks_id_seq FROM postgres;
GRANT ALL ON SEQUENCE tasks_id_seq TO postgres;


--
-- TOC entry 3210 (class 0 OID 0)
-- Dependencies: 2104
-- Name: taskschedule_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE taskschedule_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE taskschedule_id_seq FROM postgres;
GRANT ALL ON SEQUENCE taskschedule_id_seq TO postgres;


--
-- TOC entry 3212 (class 0 OID 0)
-- Dependencies: 2105
-- Name: templates_templateid_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE templates_templateid_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE templates_templateid_seq FROM postgres;
GRANT ALL ON SEQUENCE templates_templateid_seq TO postgres;


--
-- TOC entry 3214 (class 0 OID 0)
-- Dependencies: 2106
-- Name: txcategories_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE txcategories_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE txcategories_id_seq FROM postgres;
GRANT ALL ON SEQUENCE txcategories_id_seq TO postgres;


--
-- TOC entry 3216 (class 0 OID 0)
-- Dependencies: 2107
-- Name: txschedule_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE txschedule_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE txschedule_id_seq FROM postgres;
GRANT ALL ON SEQUENCE txschedule_id_seq TO postgres;


--
-- TOC entry 3218 (class 0 OID 0)
-- Dependencies: 2108
-- Name: txshows_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE txshows_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE txshows_id_seq FROM postgres;
GRANT ALL ON SEQUENCE txshows_id_seq TO postgres;


--
-- TOC entry 3220 (class 0 OID 0)
-- Dependencies: 2109
-- Name: txshowskeywords_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE txshowskeywords_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE txshowskeywords_id_seq FROM postgres;
GRANT ALL ON SEQUENCE txshowskeywords_id_seq TO postgres;


--
-- TOC entry 3222 (class 0 OID 0)
-- Dependencies: 2110
-- Name: txshowsusers_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE txshowsusers_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE txshowsusers_id_seq FROM postgres;
GRANT ALL ON SEQUENCE txshowsusers_id_seq TO postgres;


--
-- TOC entry 3224 (class 0 OID 0)
-- Dependencies: 2111
-- Name: users_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE users_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE users_id_seq FROM postgres;
GRANT ALL ON SEQUENCE users_id_seq TO postgres;


--
-- TOC entry 3226 (class 0 OID 0)
-- Dependencies: 2112
-- Name: usersconfigs_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE usersconfigs_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE usersconfigs_id_seq FROM postgres;
GRANT ALL ON SEQUENCE usersconfigs_id_seq TO postgres;


--
-- TOC entry 3228 (class 0 OID 0)
-- Dependencies: 2113
-- Name: usersgroups_id_seq; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE usersgroups_id_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE usersgroups_id_seq FROM postgres;
GRANT ALL ON SEQUENCE usersgroups_id_seq TO postgres;


-- Completed on 2009-03-15 18:55:04 GMT

--
-- PostgreSQL database dump complete
--

