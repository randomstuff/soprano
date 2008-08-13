# Doxyfile 1.5.3

#---------------------------------------------------------------------------
# Project related configuration options
#---------------------------------------------------------------------------
DOXYFILE_ENCODING      = UTF-8
PROJECT_NAME           = Soprano
PROJECT_NUMBER         = ${CMAKE_SOPRANO_VERSION_STRING}
OUTPUT_DIRECTORY       = docs
CREATE_SUBDIRS         = NO
OUTPUT_LANGUAGE        = English
BRIEF_MEMBER_DESC      = YES
REPEAT_BRIEF           = YES
ABBREVIATE_BRIEF       = "The $name class " \
                         "The $name widget " \
                         "The $name file " \
                         is \
                         provides \
                         specifies \
                         contains \
                         represents \
                         a \
                         an \
                         the
ALWAYS_DETAILED_SEC    = YES
INLINE_INHERITED_MEMB  = NO
FULL_PATH_NAMES        = YES
STRIP_FROM_PATH        = ./
STRIP_FROM_INC_PATH    = 
SHORT_NAMES            = NO
JAVADOC_AUTOBRIEF      = NO
QT_AUTOBRIEF           = YES
MULTILINE_CPP_IS_BRIEF = NO
DETAILS_AT_TOP         = NO
INHERIT_DOCS           = YES
SEPARATE_MEMBER_PAGES  = NO
TAB_SIZE               = 4
ALIASES                = 
OPTIMIZE_OUTPUT_FOR_C  = NO
OPTIMIZE_OUTPUT_JAVA   = NO
BUILTIN_STL_SUPPORT    = NO
CPP_CLI_SUPPORT        = NO
DISTRIBUTE_GROUP_DOC   = YES
SUBGROUPING            = YES
#---------------------------------------------------------------------------
# Build related configuration options
#---------------------------------------------------------------------------
EXTRACT_ALL            = YES
EXTRACT_PRIVATE        = NO
EXTRACT_STATIC         = YES
EXTRACT_LOCAL_CLASSES  = NO
EXTRACT_LOCAL_METHODS  = NO
EXTRACT_ANON_NSPACES   = NO
HIDE_UNDOC_MEMBERS     = NO
HIDE_UNDOC_CLASSES     = YES
HIDE_FRIEND_COMPOUNDS  = YES
HIDE_IN_BODY_DOCS      = NO
INTERNAL_DOCS          = YES
CASE_SENSE_NAMES       = YES
HIDE_SCOPE_NAMES       = NO
SHOW_INCLUDE_FILES     = YES
INLINE_INFO            = YES
SORT_MEMBER_DOCS       = NO
SORT_BRIEF_DOCS        = NO
SORT_BY_SCOPE_NAME     = NO
GENERATE_TODOLIST      = YES
GENERATE_TESTLIST      = YES
GENERATE_BUGLIST       = YES
GENERATE_DEPRECATEDLIST= YES
ENABLED_SECTIONS       = 
MAX_INITIALIZER_LINES  = 30
SHOW_USED_FILES        = YES
SHOW_DIRECTORIES       = NO
FILE_VERSION_FILTER    = 
#---------------------------------------------------------------------------
# configuration options related to warning and progress messages
#---------------------------------------------------------------------------
QUIET                  = NO
WARNINGS               = YES
WARN_IF_UNDOCUMENTED   = YES
WARN_IF_DOC_ERROR      = YES
WARN_NO_PARAMDOC       = NO
WARN_FORMAT            = "$file:$line: $text "
WARN_LOGFILE           = 
#---------------------------------------------------------------------------
# configuration options related to the input files
#---------------------------------------------------------------------------
INPUT                  = ${soprano_SOURCE_DIR}/soprano \
                         ${soprano_SOURCE_DIR}/Mainpage.dox \
                         ${soprano_SOURCE_DIR}/soprano/vocabulary \
                         ${soprano_SOURCE_DIR}/soprano/inference \
                         ${soprano_SOURCE_DIR}/soprano/util/ \
                         ${soprano_SOURCE_DIR}/index/indexfiltermodel.h \
                         ${soprano_SOURCE_DIR}/index/cluceneindex.h \
                         ${soprano_SOURCE_DIR}/index/indexqueryhit.h \
                         ${soprano_SOURCE_DIR}/server/SopranoServer.dox \
                         ${soprano_SOURCE_DIR}/server/servercore.h \
                         ${soprano_SOURCE_DIR}/server/tcpclient.h \
                         ${soprano_SOURCE_DIR}/server/localsocketclient.h \
                         ${soprano_SOURCE_DIR}/server/dbus/dbusclient.h \
                         ${soprano_SOURCE_DIR}/server/dbus/dbusexportmodel.h \
                         ${soprano_SOURCE_DIR}/server/dbus/dbusexportiterator.h \
                         ${soprano_SOURCE_DIR}/server/dbus/dbusmodel.h \
                         ${soprano_SOURCE_DIR}/server/dbus/dbusstatementiterator.h \
                         ${soprano_SOURCE_DIR}/server/dbus/dbusnodeiterator.h \
                         ${soprano_SOURCE_DIR}/server/dbus/dbusqueryresultiterator.h
#                         ${soprano_SOURCE_DIR}/soprano/query
INPUT_ENCODING         = UTF-8
FILE_PATTERNS          = *.h
RECURSIVE              = NO
EXCLUDE                = ${soprano_SOURCE_DIR}/soprano/datetime.h \
                         ${soprano_SOURCE_DIR}/soprano/inifile.h \
                         ${soprano_SOURCE_DIR}/soprano/desktopfile.h \
                         ${soprano_SOURCE_DIR}/soprano/sopranopluginfile.h \
                         ${soprano_SOURCE_DIR}/soprano/pluginstub.h \
                         ${soprano_SOURCE_DIR}/soprano/util/mutexiteratorbase.h \
                         ${soprano_SOURCE_DIR}/soprano/util/mutexnodeiteratorbackend.h \
                         ${soprano_SOURCE_DIR}/soprano/util/mutexstatementiteratorbackend.h \
                         ${soprano_SOURCE_DIR}/soprano/util/mutexqueryresultiteratorbackend.h \
                         ${soprano_SOURCE_DIR}/soprano/util/asynccommand.h \
                         ${soprano_SOURCE_DIR}/soprano/util/asyncmodel_p.h \
                         ${soprano_SOURCE_DIR}/soprano/util/asynciteratorbackend.h \
                         ${soprano_SOURCE_DIR}/soprano/util/asyncqueryresultiteratorbackend.h \
                         ${soprano_SOURCE_DIR}/soprano/util/extreadwritelock.h \
                         ${soprano_SOURCE_DIR}/soprano/util/simpletransactionstatementiteratorbackend.h \
                         ${soprano_SOURCE_DIR}/soprano/util/simpletransactionmodel_p.h \
                         ${soprano_SOURCE_DIR}/soprano/util/simpletransaction.h
EXCLUDE_SYMLINKS       = NO
EXCLUDE_PATTERNS       = 
EXCLUDE_SYMBOLS        = 
EXAMPLE_PATH           = 
EXAMPLE_PATTERNS       = *
EXAMPLE_RECURSIVE      = NO
IMAGE_PATH             = 
INPUT_FILTER           = 
FILTER_PATTERNS        = 
FILTER_SOURCE_FILES    = NO
#---------------------------------------------------------------------------
# configuration options related to source browsing
#---------------------------------------------------------------------------
SOURCE_BROWSER         = YES
INLINE_SOURCES         = NO
STRIP_CODE_COMMENTS    = YES
REFERENCED_BY_RELATION = NO
REFERENCES_RELATION    = NO
REFERENCES_LINK_SOURCE = YES
USE_HTAGS              = NO
VERBATIM_HEADERS       = NO
#---------------------------------------------------------------------------
# configuration options related to the alphabetical class index
#---------------------------------------------------------------------------
ALPHABETICAL_INDEX     = YES
COLS_IN_ALPHA_INDEX    = 5
IGNORE_PREFIX          = 
#---------------------------------------------------------------------------
# configuration options related to the HTML output
#---------------------------------------------------------------------------
GENERATE_HTML          = YES
HTML_OUTPUT            = html
HTML_FILE_EXTENSION    = .html
HTML_HEADER            = 
HTML_FOOTER            = 
HTML_STYLESHEET        = 
HTML_ALIGN_MEMBERS     = YES
GENERATE_HTMLHELP      = NO
HTML_DYNAMIC_SECTIONS  = YES
CHM_FILE               = 
HHC_LOCATION           = 
GENERATE_CHI           = NO
BINARY_TOC             = NO
TOC_EXPAND             = NO
DISABLE_INDEX          = NO
ENUM_VALUES_PER_LINE   = 4
GENERATE_TREEVIEW      = NO
TREEVIEW_WIDTH         = 250
#---------------------------------------------------------------------------
# configuration options related to the LaTeX output
#---------------------------------------------------------------------------
GENERATE_LATEX         = NO
LATEX_OUTPUT           = latex
LATEX_CMD_NAME         = latex
MAKEINDEX_CMD_NAME     = makeindex
COMPACT_LATEX          = NO
PAPER_TYPE             = a4wide
EXTRA_PACKAGES         = 
LATEX_HEADER           = 
PDF_HYPERLINKS         = NO
USE_PDFLATEX           = NO
LATEX_BATCHMODE        = NO
LATEX_HIDE_INDICES     = NO
#---------------------------------------------------------------------------
# configuration options related to the RTF output
#---------------------------------------------------------------------------
GENERATE_RTF           = NO
RTF_OUTPUT             = rtf
COMPACT_RTF            = NO
RTF_HYPERLINKS         = NO
RTF_STYLESHEET_FILE    = 
RTF_EXTENSIONS_FILE    = 
#---------------------------------------------------------------------------
# configuration options related to the man page output
#---------------------------------------------------------------------------
GENERATE_MAN           = NO
MAN_OUTPUT             = man
MAN_EXTENSION          = .3
MAN_LINKS              = NO
#---------------------------------------------------------------------------
# configuration options related to the XML output
#---------------------------------------------------------------------------
GENERATE_XML           = NO
XML_OUTPUT             = xml
XML_SCHEMA             = 
XML_DTD                = 
XML_PROGRAMLISTING     = YES
#---------------------------------------------------------------------------
# configuration options for the AutoGen Definitions output
#---------------------------------------------------------------------------
GENERATE_AUTOGEN_DEF   = NO
#---------------------------------------------------------------------------
# configuration options related to the Perl module output
#---------------------------------------------------------------------------
GENERATE_PERLMOD       = NO
PERLMOD_LATEX          = NO
PERLMOD_PRETTY         = YES
PERLMOD_MAKEVAR_PREFIX = 
#---------------------------------------------------------------------------
# Configuration options related to the preprocessor   
#---------------------------------------------------------------------------
ENABLE_PREPROCESSING   = YES
MACRO_EXPANSION        = YES
EXPAND_ONLY_PREDEF     = YES
SEARCH_INCLUDES        = YES
INCLUDE_PATH           = 
INCLUDE_FILE_PATTERNS  = 
PREDEFINED             = 
EXPAND_AS_DEFINED      = EIGEN_MAKE_DYNAMICSIZE_TYPEDEFS \
                         EIGEN_MAKE_FIXEDSIZE_TYPEDEFS
SKIP_FUNCTION_MACROS   = YES
#---------------------------------------------------------------------------
# Configuration::additions related to external references   
#---------------------------------------------------------------------------
TAGFILES               = ${soprano_SOURCE_DIR}/qt4.tag
GENERATE_TAGFILE       = 
ALLEXTERNALS           = NO
EXTERNAL_GROUPS        = YES
PERL_PATH              = /usr/bin/perl
#---------------------------------------------------------------------------
# Configuration options related to the dot tool   
#---------------------------------------------------------------------------
CLASS_DIAGRAMS         = YES
MSCGEN_PATH            = 
HIDE_UNDOC_RELATIONS   = YES
HAVE_DOT               = YES
CLASS_GRAPH            = YES
COLLABORATION_GRAPH    = NO
GROUP_GRAPHS           = YES
UML_LOOK               = NO
TEMPLATE_RELATIONS     = YES
INCLUDE_GRAPH          = YES
INCLUDED_BY_GRAPH      = YES
CALL_GRAPH             = NO
CALLER_GRAPH           = NO
GRAPHICAL_HIERARCHY    = YES
DIRECTORY_GRAPH        = YES
DOT_IMAGE_FORMAT       = png
DOT_PATH               = 
DOTFILE_DIRS           = 
DOT_GRAPH_MAX_NODES    = 50
MAX_DOT_GRAPH_DEPTH    = 1000
DOT_TRANSPARENT        = YES
DOT_MULTI_TARGETS      = NO
GENERATE_LEGEND        = YES
DOT_CLEANUP            = YES
#---------------------------------------------------------------------------
# Configuration::additions related to the search engine   
#---------------------------------------------------------------------------
SEARCHENGINE           = NO
