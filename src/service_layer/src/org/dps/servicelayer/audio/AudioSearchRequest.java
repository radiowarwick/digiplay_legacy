package org.dps.servicelayer.audio;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;

@XmlAccessorType(XmlAccessType.NONE)
public class AudioSearchRequest {
	private List<SearchKey> searchKey = new LinkedList<SearchKey>();

	
	@XmlElement(required = true)
	@XmlElementWrapper(name="searchKeys", required = true)
	protected List<SearchKey> getSearchKey() {
		return searchKey;
	}	
	protected void setSearchKey(List<SearchKey> searchKey) {
		this.searchKey = searchKey;
	}

	public Map<String, String> getSearchKeysAsMap() {
		Map<String, String> results = new HashMap<String, String>(searchKey.size());
		for(SearchKey entry : searchKey) {
			results.put(entry.key, entry.value);
		}
		return results;
	}
	public void addSearchKey(String key, String value) {
		searchKey.add(new SearchKey(key, value));
	}
	
	public static class SearchKey {
		String key;
		String value;
		public SearchKey() {
			
		}
		public SearchKey(String key, String value) {
			this.key = key;
			this.value = value;
		}
		public String getKey() {
			return key;
		}
		public void setKey(String key) {
			this.key = key;
		}
		public String getValue() {
			return value;
		}
		public void setValue(String value) {
			this.value = value;
		}
		
	}




}
