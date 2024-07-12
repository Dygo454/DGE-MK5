<map version="freeplane 1.11.5">
<!--To view this file, download free mind mapping software Freeplane from https://www.freeplane.org -->
<node TEXT="Main" LOCALIZED_STYLE_REF="AutomaticLayout.level.root" FOLDED="false" ID="ID_1090958577" CREATED="1409300609620" MODIFIED="1720774517052"><hook NAME="MapStyle" background="#2e3440" zoom="0.754">
    <properties show_icon_for_attributes="true" edgeColorConfiguration="#808080ff,#ff0000ff,#0000ffff,#00ff00ff,#ff00ffff,#00ffffff,#7c0000ff,#00007cff,#007c00ff,#7c007cff,#007c7cff,#7c7c00ff" show_note_icons="true" associatedTemplateLocation="template:/dark_nord_template.mm" followedTemplateLocation="template:/dark_nord_template.mm" followedMapLastTime="1714597358000" fit_to_viewport="false"/>

<map_styles>
<stylenode LOCALIZED_TEXT="styles.root_node" STYLE="oval" UNIFORM_SHAPE="true" VGAP_QUANTITY="24 pt">
<font SIZE="24"/>
<stylenode LOCALIZED_TEXT="styles.predefined" POSITION="bottom_or_right" STYLE="bubble">
<stylenode LOCALIZED_TEXT="default" ID="ID_671184412" ICON_SIZE="12 pt" FORMAT_AS_HYPERLINK="false" COLOR="#484747" BACKGROUND_COLOR="#eceff4" STYLE="bubble" SHAPE_HORIZONTAL_MARGIN="8 pt" SHAPE_VERTICAL_MARGIN="5 pt" BORDER_WIDTH_LIKE_EDGE="false" BORDER_WIDTH="1.9 px" BORDER_COLOR_LIKE_EDGE="true" BORDER_COLOR="#f0f0f0" BORDER_DASH_LIKE_EDGE="true" BORDER_DASH="SOLID">
<arrowlink SHAPE="CUBIC_CURVE" COLOR="#88c0d0" WIDTH="2" TRANSPARENCY="255" DASH="" FONT_SIZE="9" FONT_FAMILY="SansSerif" DESTINATION="ID_671184412" STARTARROW="NONE" ENDARROW="DEFAULT"/>
<font NAME="SansSerif" SIZE="11" BOLD="false" STRIKETHROUGH="false" ITALIC="false"/>
<edge STYLE="bezier" COLOR="#81a1c1" WIDTH="3" DASH="SOLID"/>
<richcontent TYPE="DETAILS" CONTENT-TYPE="plain/auto"/>
<richcontent TYPE="NOTE" CONTENT-TYPE="plain/auto"/>
</stylenode>
<stylenode LOCALIZED_TEXT="defaultstyle.details" BORDER_WIDTH="1.9 px">
<edge STYLE="bezier" COLOR="#81a1c1" WIDTH="3"/>
</stylenode>
<stylenode LOCALIZED_TEXT="defaultstyle.attributes">
<font SIZE="10"/>
</stylenode>
<stylenode LOCALIZED_TEXT="defaultstyle.note" COLOR="#000000" BACKGROUND_COLOR="#ebcb8b">
<icon BUILTIN="clock2"/>
<font SIZE="10"/>
</stylenode>
<stylenode LOCALIZED_TEXT="defaultstyle.floating" COLOR="#484747">
<edge STYLE="hide_edge"/>
<cloud COLOR="#f0f0f0" SHAPE="ROUND_RECT"/>
</stylenode>
<stylenode LOCALIZED_TEXT="defaultstyle.selection" COLOR="#e5e9f0" BACKGROUND_COLOR="#5e81ac" BORDER_COLOR_LIKE_EDGE="false" BORDER_COLOR="#5e81ac"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.user-defined" POSITION="bottom_or_right" STYLE="bubble">
<stylenode LOCALIZED_TEXT="styles.important" ID="ID_779275544" BORDER_COLOR_LIKE_EDGE="false" BORDER_COLOR="#bf616a">
<icon BUILTIN="yes"/>
<arrowlink COLOR="#bf616a" TRANSPARENCY="255" DESTINATION="ID_779275544"/>
<font SIZE="14"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.flower" COLOR="#ffffff" BACKGROUND_COLOR="#255aba" STYLE="oval" TEXT_ALIGN="CENTER" BORDER_WIDTH_LIKE_EDGE="false" BORDER_WIDTH="22 pt" BORDER_COLOR_LIKE_EDGE="false" BORDER_COLOR="#f9d71c" BORDER_DASH_LIKE_EDGE="false" BORDER_DASH="CLOSE_DOTS" MAX_WIDTH="6 cm" MIN_WIDTH="3 cm"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.AutomaticLayout" POSITION="bottom_or_right" STYLE="bubble">
<stylenode LOCALIZED_TEXT="AutomaticLayout.level.root" COLOR="#ffffff" BACKGROUND_COLOR="#484747" STYLE="bubble" SHAPE_HORIZONTAL_MARGIN="10 pt" SHAPE_VERTICAL_MARGIN="10 pt">
<font NAME="Ubuntu" SIZE="18"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,1" COLOR="#eceff4" BACKGROUND_COLOR="#d08770" STYLE="bubble" SHAPE_HORIZONTAL_MARGIN="8 pt" SHAPE_VERTICAL_MARGIN="5 pt">
<font NAME="Ubuntu" SIZE="16"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,2" COLOR="#3b4252" BACKGROUND_COLOR="#ebcb8b">
<font SIZE="14"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,3" COLOR="#2e3440" BACKGROUND_COLOR="#a3be8c">
<font SIZE="12"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,4" COLOR="#2e3440" BACKGROUND_COLOR="#b48ead">
<font SIZE="11"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,5" BACKGROUND_COLOR="#81a1c1">
<font SIZE="10"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,6" BACKGROUND_COLOR="#88c0d0">
<font SIZE="10"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,7" BACKGROUND_COLOR="#8fbcbb">
<font SIZE="10"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,8" BACKGROUND_COLOR="#d8dee9">
<font SIZE="10"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,9" BACKGROUND_COLOR="#e5e9f0">
<font SIZE="9"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,10" BACKGROUND_COLOR="#eceff4">
<font SIZE="9"/>
</stylenode>
</stylenode>
</stylenode>
</map_styles>
</hook>
<hook NAME="accessories/plugins/AutomaticLayout.properties" VALUE="ALL"/>
<font BOLD="true"/>
<node TEXT="RendPipeline" LOCALIZED_STYLE_REF="defaultstyle.floating" POSITION="bottom_or_right" ID="ID_5923153" CREATED="1720774430073" MODIFIED="1720774530268" HGAP_QUANTITY="-626.40001 pt" VSHIFT_QUANTITY="-255.00001 pt">
<hook NAME="FreeNode"/>
<node TEXT="ContextQueue* q;" POSITION="bottom_or_right" ID="ID_514572967" CREATED="1720771210826" MODIFIED="1720775153433"/>
<node TEXT="RendPipeline(vector&lt;Stage&gt;);" POSITION="bottom_or_right" ID="ID_305954388" CREATED="1720768701926" MODIFIED="1720773625410"/>
<node TEXT="vector&lt;Stage&gt; stages;" POSITION="bottom_or_right" ID="ID_1683407045" CREATED="1720767793173" MODIFIED="1720767821286">
<node TEXT="Stage" ID="ID_19469854" CREATED="1720767832093" MODIFIED="1720767837754">
<node TEXT="Stage(Kernel, string, int);" ID="ID_1783807311" CREATED="1720768785533" MODIFIED="1720770928427">
<node TEXT="kernel" ID="ID_36855810" CREATED="1720770930201" MODIFIED="1720770956461"/>
<node TEXT="error string" ID="ID_174886356" CREATED="1720770943562" MODIFIED="1720770951349"/>
<node TEXT="error code" ID="ID_1515163210" CREATED="1720770944659" MODIFIED="1720770958532"/>
</node>
<node TEXT="void pass(Buffer, ContextQueue);" ID="ID_1428301381" CREATED="1720770859949" MODIFIED="1720771204289"/>
<node TEXT="static unordered_map&lt;int, string&gt; errorCodes;" ID="ID_1249564300" CREATED="1720771039959" MODIFIED="1720771062424"/>
<node TEXT="static void initKernels();" ID="ID_1645685322" CREATED="1720774822908" MODIFIED="1720774832750"/>
</node>
</node>
<node TEXT="void pipe(Buffer, CameraSettings);" POSITION="bottom_or_right" ID="ID_1168511346" CREATED="1720767646698" MODIFIED="1720771281525"/>
<node TEXT="static RendPipeline Default" POSITION="bottom_or_right" ID="ID_1930764510" CREATED="1720767741044" MODIFIED="1720773629972">
<node TEXT="stages" POSITION="bottom_or_right" ID="ID_1952967632" CREATED="1720766927146" MODIFIED="1720767825410">
<node TEXT="Stage" ID="ID_607891914" CREATED="1720767000676" MODIFIED="1720767012129">
<node TEXT="VertexShader" ID="ID_1068788154" CREATED="1720767049758" MODIFIED="1720767089882"/>
</node>
<node TEXT="Stage" ID="ID_494174218" CREATED="1720767000676" MODIFIED="1720767012129">
<node TEXT="PrimitiveAssempbly" ID="ID_1931980257" CREATED="1720767001163" MODIFIED="1720767399734"/>
</node>
<node TEXT="Stage" ID="ID_648819339" CREATED="1720767000676" MODIFIED="1720767012129">
<node TEXT="Rasterization" ID="ID_323485098" CREATED="1720767000676" MODIFIED="1720767406465"/>
</node>
<node TEXT="Stage" ID="ID_1746026009" CREATED="1720767000676" MODIFIED="1720767012129">
<node TEXT="PixelShader" ID="ID_1731606765" CREATED="1720767000676" MODIFIED="1720767417451"/>
</node>
<node TEXT="Stage" ID="ID_1043966396" CREATED="1720767000676" MODIFIED="1720767600068">
<node TEXT="DepthShader" ID="ID_1734510363" CREATED="1720767000676" MODIFIED="1720767515689"/>
</node>
<node TEXT="Stage" ID="ID_42603796" CREATED="1720767603277" MODIFIED="1720767606266">
<node TEXT="AlphaBlending" ID="ID_885103723" CREATED="1720767613461" MODIFIED="1720767618149"/>
</node>
</node>
</node>
<node TEXT="static void initDefault();" ID="ID_734715466" CREATED="1720774746178" MODIFIED="1720774790582">
<node TEXT="Stage::initKernels();" ID="ID_540789367" CREATED="1720774792585" MODIFIED="1720774820255"/>
</node>
</node>
</node>
</map>