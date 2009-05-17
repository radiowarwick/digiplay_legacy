package org.dps.servicelayer.cartset;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

import org.dps.servicelayer.Namespaces;
import org.dps.servicelayer.common.ResultSetControl;


@XmlAccessorType(XmlAccessType.NONE)
public class CartsetsRequest {
    private ResultSetControl resultSetControl;

    @XmlElement(required = true, namespace = Namespaces.COMMON)
	public ResultSetControl getResultSetControl() {
		return resultSetControl;
	}
	public void setResultSetControl(ResultSetControl resultSetControl_) {
		resultSetControl = resultSetControl_;
	}
}
