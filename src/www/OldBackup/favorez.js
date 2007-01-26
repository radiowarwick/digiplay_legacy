/* Favorez "My Favorites" JavaScript
 * copyright (c) 2002 WarpGear Software
 *
 * You are permitted to use this code under the conditions
 * outlined by an M.I.T. style license. According to this
 * license, you may not remove this copyright notice.
 * The complete text of the license can be found here: 
 * http://www.favorez.com/my_favorites_license.txt
 *
 * version: 1.1
 * date: December 1, 2003
 * website: http://www.favorez.com
 * author: Tom Kalmijn
 */

// define globals
var fzId = 0; // counter to obtain unique FZNode id's
var fzSel = 0; // id of last clicked link 
var fzNodes = new Array(); // lookup list for nodes, FZNode.id equals the position of a node in the list.
var fzRoot; // FZNode: fzRoot of all nodes, acts as an anchor for the whole in-memory tree structure.
var fzIndents = new Array();
var fzIndentSize = 4;
var fzTarget = "_blank";
var fzFilter = "";
if (typeof(fzCodebase)=="undefined") fzCodebase = '';

// Netscape compatibility var
var ns4 = document.layers; // alias for frequently used switch
var ns4_html = ""; // off screen buffer to render html
var ns4_draw = false; // switch for special ns4 drawing
// counteract NS4 infamous resize bug...
var winW = window.innerWidth;
var winH = window.innerHeight;
function onResize() {
    if (ns4) {
        if (winW != window.innerWidth ||
            winH != window.innerHeight) {
            location.reload(true);
        }
    }
}

// declare & define class FZNode
// *** this class is browser independant, no html allowed ***
function FZNode(canExpand) {
    this.id = 0;
    this.subNodes = null;
    this.parent = null;
    this.isExpanded = false;
    this.canExpand = canExpand;
    this.visible = false;
    this.nesting = -1;

    // assign methods (needs to be done only once)
    if (typeof(_FZNode_prototype_called) == "undefined") {
        _FZNode_prototype_called = true;
        FZNode.prototype.expand = expand;
        FZNode.prototype.add = add;
        FZNode.prototype.show = show;
    }
    
    function add(node) {
        // init subNodes lazily
        if (!this.subNodes) 
            this.subNodes = new Array();
        node.parent = this;
        node.nesting = this.nesting+1;
        node.index = this.subNodes.length;
        this.subNodes[node.index] = node;
        fzNodes[node.id] = node;

        return node;
    }    

    function expand(expand, recurse) {
        if (this.subNodes) {
            var len = this.subNodes.length;
            for (var n = 0; n < len; n++) {
                var node = this.subNodes[n];

                if (node.canExpand && recurse) {
                    node.isExpanded = expand;
                }
                node.show(expand); // JavaScript polymorphism at work!

                if (node.canExpand && (recurse || !expand || node.isExpanded)) {
                    node.expand(expand, recurse);
                }
            }
        }
    }

    function show() { /* abstract */ alert("error in JavaScript inheritance structure!"); }
}

// FZFolder extends FZNode, renders a node as a folder.
// (see prototype assignment at end of class)
function FZFolder(name) {
    this.id = fzId++; 
    this.name = name;

    // assign methods
    if (typeof(_FZFolder_prototype_called) == "undefined") {
        _FZFolder_prototype_called = true;
        FZFolder.prototype.al = al;
        FZFolder.prototype.af = af;
        FZFolder.prototype.show = show; // override abstract FZNode.show
    }

    function al(title, path, icon) {
        return this.add(new FZUrl(title, path, icon));
    }
    
    function af(name) {
        return this.add(new FZFolder(name));
    }

    function show(show) {
        if (this == fzRoot) return;

        if (this.visible || show) {
            this.visible = show;
            if (!this.div && !ns4) this.div = fzElement("fz"+this.id);

            if (show) {
                var html = "";
                if ((!this.html_open && this.isExpanded) || (!this.html_closed && !this.isExpanded)) {
                    html = "<table width=\"100%\" cellpadding=\"0\" cellspacing=\"0\" border=\"0\">";
                    html += "<tr nowrap><td height=\"20\" valign=\"bottom\">" + fzIndents[this.nesting];
                    html += "<a onClick=\"javascript:void(0);\" href=\"javascript:fzExpand('" + this.id + "');\"><img";
                    if (fzFilter != "") html += " style=\"filter:progid:DXImageTransform.Microsoft." + fzFilter + "\"";
                    html += " align=\"absmiddle\" width=\"16px\" height=\"16px\" src=\""+fzCodebase;
                    html += (this.isExpanded) ? "03.png" : "02.png";
                    html += "\" border=\"0\"></a></td><td width=\"100%\" align=\"left\" >&nbsp;<font size=\"" + fzFontSize + "\">";
                    html += "<a onClick=\"javascript:void(0);\" href=\"javascript:fzExpand('" + this.id + "');\">" + this.name + "</a></font></td>";
                    html += "</tr></table>";
                    if (this.isExpanded)
                        this.html_open = html;
                    else
                        this.html_closed = html;
                }
                html = this.isExpanded ? this.html_open : this.html_closed;

                if (ns4) { if (ns4_draw) ns4_html += html; }
                else fzWrite(this.div, html);
            }
            if (!ns4) this.div.style.display = show ? "" : "none";
        }
    }
}
FZFolder.prototype = new FZNode(true); 

// FZUrl extends FZNode, renders a node as an url.
function FZUrl(title, path, icon) {
    this.id = fzId++;
    this.title = title;
    this.path = path;
    this.icon = icon;
    this.selected = false;

    if (typeof(_FZUrl_prototype_called) == "undefined") {
        _FZUrl_prototype_called = true;
        FZUrl.prototype.show = show;
    }

    function show(show) {
        if (this.visible || show) {
            this.visible = show;
            if (!this.div && !ns4) this.div = fzElement("fz"+this.id);

            var s = (this.id - fzSel == 0); 
            var redraw = !this.html || (this.selected != s);
            this.selected = s;
                        
            if (show && redraw) {
                this.html = "<table width=\"100%\" cellpadding=\"0\" cellspacing=\"0\" border=\"0\"><tr nowrap><td height=\"20\" valign=\"bottom\">" + fzIndents[this.nesting];
                this.html += "<a onClick=\"fzSelect('" + this.id + "')\" href=\"" + this.path + "\" target=\"" + fzTarget + "\"><img";
                if (fzFilter != "") this.html += " style=\"filter:progid:DXImageTransform.Microsoft." + fzFilter + "\"";                
                this.html += " align=\"absmiddle\" width=\"16px\" height=\"16px\" src=\"" + fzCodebase + this.icon + "\" alt=\"" + this.path + "\" border=\"0\"></a></td>";
                this.html += "<td nowrap width=\"100%\">&nbsp;<a onClick=\"fzSelect('" + this.id + "')\" href=\"" + this.path + "\" target=\"" + fzTarget + "\"><font size=\"" + fzFontSize + "\">";
                this.html += s ? "<b>" + this.title + "</b>" : this.title;
                this.html += "</font></a></td></tr></table>";
                if (!ns4) fzWrite(this.div, this.html);                        
            }
            if (ns4) { if (ns4_draw) ns4_html += this.html; }
            else this.div.style.display = show ? "" : "none";
        }
    }
}
FZUrl.prototype = new FZNode(false);

function fzUpdateNode(id) {
    var node = fzNodes[id];  
    if (node) node.show(node.visible);
}

// update selection status
function fzSelect(id) {
    var prevId = fzSel;
    fzSel = id;    

    if (ns4) {
        setTimeout("fzRenderTree()", 200); 
    }
    else { 
        setTimeout("fzUpdateNode(" + prevId + ")", 200); 
        setTimeout("fzUpdateNode(" + fzSel + ")", 200);
    }
}

// render whole tree structure (for NS4 only)
function fzRenderTree() {
    ns4_html = ""; // reset buffer to render
    ns4_draw = true;
    fzShow(fzRoot);
    ns4_draw = false;
    fzWrite(document.ns4_tree, ns4_html);
}

function fzShow(node) {
    node.show(true);
    if (node.canExpand) {
        if (node.isExpanded && node.subNodes) {
            var len = node.subNodes.length;
            for (var n = 0; n < len; n++) {
                var subNode = node.subNodes[n];
                fzShow(subNode);
            }
        }
    }
}

function fzExpand(id, recurse) {
    var node = fzNodes[id];
    if (node) {
        if (node.canExpand) {
            var expand = !node.isExpanded;
            node.isExpanded = expand;
            node.show(true);
            node.expand(expand, recurse);
            if (ns4) fzRenderTree();
        }
    }
}

function fzExpandAll(doExpand) {
    fzRoot.isExpanded = !doExpand;
    fzExpand(fzRoot.id, true);
    if (!doExpand) fzExpand(fzRoot.id, false); // always expand at least one level
}

// Browser compatibility wrappers...
function fzWrite(obj, html) {
    if (document.getElementById || document.all) { // IE 4+ & Netscape 6+
        obj.innerHTML = html;
    }
    else if (ns4) { // Netscape 4+
        obj.document.open();
        obj.document.write(html);
        obj.document.close();
    }
}

function fzElement(id) {
    if (document.getElementById) { // IE 5+ & Netscape 6+
        return document.getElementById(id);
    }
    else if (document.all) { // IE 4+
        return document.all[id];
    }
    else if (ns4) { // Netscape 4+
        return document[id];
    }
    return null;
}

function setTreePos() {
    if (ns4) {
        var anchor = document.anchors["ns4_tree_anchor"];
        document.ns4_tree.pageX = anchor.x;
        document.ns4_tree.pageY = anchor.y;
        document.ns4_tree.visibility = "visible";
    }   
}       

function fzInit() {
    for (var indent = 0; indent < 16; indent++) {
        var sIndent = "&nbsp;";
        for (var i = 0; i < indent*fzIndentSize; i++) {
            sIndent += "&nbsp;";
        }
        fzIndents[indent] = sIndent;
    }
    setTreePos();
    fzExpand(fzRoot.id);
    if (ns4) window.onresize=onResize;
}

function fzDivs() {
    var d = document;
    if (ns4) {
       d.open();
       d.write("<a name=\"ns4_tree_anchor\">&nbsp;</a>");
       d.write("<table height=\"" + fzId * 20 + "\" border=\"0\"><tr><td>&nbsp;</td></tr></table><br>");
       d.close();
    }
    else {
        for (var i = 0; i <= fzId; i++) {
            // create DIVs (these will hold our folders and urls)
            d.write("<div id=\"fz" + i + "\" style=\"display:none\"></div>");
        }
    }
}

