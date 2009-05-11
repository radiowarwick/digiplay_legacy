package org.dps.servicelayer.common;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;

@XmlAccessorType(XmlAccessType.FIELD)
public class ResultSetControl {
	
	@XmlElement(required = false, name = "sortByColumn")
	@XmlElementWrapper(name = "sortByColumns")
	private List<String> sortByColumns = new ArrayList<String>();
	
	@XmlElement(required = false)
	private Integer resultsPerPage = null;
	
	@XmlElement(required = false)
	private Integer pageNum = Integer.valueOf(0);
	
	@XmlElement(required = false)
	private boolean invertSearch = false;
	
	public List<String> getSortByColumns() {
		return Collections.unmodifiableList(sortByColumns);
	}
	public void setSortByColumns(List<String> sortByColumns_) {
		sortByColumns = sortByColumns_;
	}
	public void addSortByColumn(String column) {
		sortByColumns.add(column);
	}
	public void removeSortByColumn(String column) {
		sortByColumns.remove(column);
	}
	public void clearSortByColumn(String column) {
		sortByColumns.clear();
	}
	public Integer getResultsPerPage() {
		return resultsPerPage;
	}
	public void setResultsPerPage(Integer resultsPerPage_) {
		resultsPerPage = resultsPerPage_;
	}
	public Integer getPageNum() {
		return pageNum;
	}
	public void setPageNum(Integer pageNum_) {
		pageNum = pageNum_;
	}
	public boolean isInvertSearch() {
		return invertSearch;
	}
	public void setInvertSearch(boolean invertSearch_) {
		invertSearch = invertSearch_;
	}
	
}
