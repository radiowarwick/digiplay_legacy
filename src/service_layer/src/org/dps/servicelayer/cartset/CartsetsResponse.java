package org.dps.servicelayer.cartset;

import java.util.ArrayList;
import java.util.List;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;

import org.dps.servicelayer.Namespaces;
import org.dps.servicelayer.common.ResultSetDetails;

@XmlAccessorType(XmlAccessType.PROPERTY)
public class CartsetsResponse {
	
    private List<PermissionedCartsetSummary> permissionedCartsetSummaries = new ArrayList<PermissionedCartsetSummary>();
    private ResultSetDetails resultSetDetails;

    public CartsetsResponse() {    	
    }
    
    public CartsetsResponse(CartsetsRequest request) {
    	this.resultSetDetails = new ResultSetDetails(request.getResultSetControl());
    }
    
    @XmlElement(name = "permissionedCartsetSummary", required = false)
    @XmlElementWrapper(name = "permissionedCartsetSummaries")
	public List<PermissionedCartsetSummary> getPermissionedCartsetSummaries() {
		return permissionedCartsetSummaries;
	}
	public void setPermissionedCartsetSummaries(
			List<PermissionedCartsetSummary> permissionedCartsetSummaries_) {
		permissionedCartsetSummaries = permissionedCartsetSummaries_;
	}	
	public void addPermissionedCartsetSummary(
			PermissionedCartsetSummary permSummary_) {
		permissionedCartsetSummaries.add(permSummary_);
	}
	
	@XmlElement(required = true, namespace = Namespaces.COMMON)
	public ResultSetDetails getResultSetDetails() {
		return resultSetDetails;
	}
	public void setResultSetDetails(ResultSetDetails resultSetDetails_) {
		resultSetDetails = resultSetDetails_;
	}
}